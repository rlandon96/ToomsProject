// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	OurCameraSpringArm->SetupAttachment(RootComponent);
	OurCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(0.0f, 0.0f, 0.0f));
	OurCameraSpringArm->TargetArmLength = 0.0f;
	OurCameraSpringArm->bEnableCameraLag = true;
	OurCameraSpringArm->CameraLagSpeed = 3.0f;
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
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
	willStop = true;
}

void AMyPawn::MoveUp()
{
	if (!isMoving) {
		isMoving = true;
		keyPressed = 0;
		GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AMyPawn::MovePawn, 0.03f, true, 0.0f);
	}
}

void AMyPawn::MoveRight()
{
	if (!isMoving) {
		isMoving = true;
		keyPressed = 1;
		GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AMyPawn::MovePawn, 0.03f, true, 0.0f);
	}
}

void AMyPawn::MoveDown()
{
	if (!isMoving) {
		isMoving = true;
		keyPressed = 2;
		GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AMyPawn::MovePawn, 0.03f, true, 0.0f);
	}
}

void AMyPawn::MoveLeft()
{
	if (!isMoving) {
		isMoving = true;
		keyPressed = 3;
		GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AMyPawn::MovePawn, 0.03f, true, 0.0f);
	}
}

void AMyPawn::MovePawn()
{
	FVector movementDirection = Directions[keyPressed];
	AddActorLocalOffset(movementDirection * stepSize);
	moveCalls--;
	if (moveCalls == 0)
	{
		moveCalls = 20;
		if (willStop) {
			isMoving = false;
			willStop = false;
			GetWorldTimerManager().ClearTimer(MemberTimerHandle);
		}
	}
}
void AMyPawn::RotateLeft()
{
	if(!isMoving)
	AddActorLocalRotation(FRotator(0, -90, 0));
}

void AMyPawn::RotateRight()
{
	if(!isMoving)
	AddActorLocalRotation(FRotator(0, 90, 0));
}