// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

// Sets default values
AMyPawn::AMyPawn()
	{
	current = ALevelManager::getGrid();
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	OurCameraSpringArm->SetupAttachment(RootComponent);
	OurCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 75.0f), FRotator(0.0f, 0.0f, 0.0f));
	OurCameraSpringArm->TargetArmLength = 0.0f;
	OurCameraSpringArm->bEnableCameraLag = true;
	OurCameraSpringArm->CameraLagSpeed = 3.0f;
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));

	OurCamera->SetRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));
	OurCamera->SetupAttachment(OurCameraSpringArm, USpringArmComponent::SocketName);
	}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAction("Up", IE_Pressed, this, &AMyPawn::MoveUp);
	InputComponent->BindAction("Up", IE_Released, this, &AMyPawn::StopPawn);

	InputComponent->BindAction("Strafe Right", IE_Pressed, this, &AMyPawn::MoveRight);
	InputComponent->BindAction("Strafe Right", IE_Released, this, &AMyPawn::StopPawn);

	InputComponent->BindAction("Down", IE_Pressed, this, &AMyPawn::MoveDown);
	InputComponent->BindAction("Down", IE_Released, this, &AMyPawn::StopPawn);

	InputComponent->BindAction("Strafe Left", IE_Pressed, this, &AMyPawn::MoveLeft);
	InputComponent->BindAction("Strafe Left", IE_Released, this, &AMyPawn::StopPawn);

	InputComponent->BindAction("Turn Left", IE_Pressed, this, &AMyPawn::RotateLeft);
	InputComponent->BindAction("Turn Right", IE_Pressed, this, &AMyPawn::RotateRight);
}

void AMyPawn::StopPawn()
{
	if (isMoving) {
		willStop = true;
	}
}

void AMyPawn::MoveUp()
{
	if (!isMoving) {
		if (ValidMovement(0)) {
			keyPressed = 0;
			StartMove();
		}
	}
}

void AMyPawn::MoveRight()
{
	if (!isMoving) {
		if (ValidMovement(1)) {
			keyPressed = 1;
			StartMove();
		}
	}
}

void AMyPawn::MoveDown()
{
	if (!isMoving) {
		if (ValidMovement(2)) {
			keyPressed = 2;
			StartMove();
		}
	}
}

void AMyPawn::MoveLeft()
{
	if (!isMoving) {
		if (ValidMovement(3)) {
			keyPressed = 3;
			StartMove();
		}
	}
}

bool AMyPawn::ValidMovement(int directionIndex)
{
	int direction = int(round(GetActorRotation().Yaw) / 90 + directionIndex + 4)%4;
	if(direction ==0)
	{
		if ((*current).validSpot(indexX, indexY + 1)) {
			indexY++;
			return true;
		}
	}
	else if (direction == 1)
	{
		if ((*current).validSpot(indexX + 1, indexY)) {
			indexX++;
			return true;
		}
	}
	else if (direction == 2)
	{
		if ((*current).validSpot(indexX, indexY - 1)) {
			indexY--;
			return true;
		}
	}
	else if (direction == 3)
	{
		if ((*current).validSpot(indexX-1, indexY)) {
			indexX--;
			return true;
		}
	}
	return false;
}


void AMyPawn::StartMove()
{
	willStop = false;
	isMoving = true;
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AMyPawn::MovePawn, 0.016f, true, 0.01f);
}

void AMyPawn::MovePawn()
{
	FVector movementDirection = Directions[keyPressed];
	AddActorLocalOffset(movementDirection * stepSize);
	moveCalls--;
	if (moveCalls == 0)
	{
		moveCalls = initialMoveCalls;
		if (willStop) {
			isMoving = false;
			willStop = false;
			GetWorldTimerManager().ClearTimer(MemberTimerHandle);
		}
		else if (!ValidMovement(keyPressed))
		{
			isMoving = false;
			GetWorldTimerManager().ClearTimer(MemberTimerHandle);
		}
	}
}
void AMyPawn::RotateLeft()
{
	if (!isMoving)
		AddActorLocalRotation(FRotator(0, -90, 0));
}

void AMyPawn::RotateRight()
{
	if (!isMoving)
		AddActorLocalRotation(FRotator(0, 90, 0));
}

