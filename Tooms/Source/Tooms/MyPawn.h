// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "TimerManager.h"
#include "MyPawn.generated.h" //Must be last


UCLASS()
class TOOMS_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();
	bool isMoving = false;
	bool willStop = false;
	int initialMoveCalls = 30;
	int moveCalls = initialMoveCalls;
	int stepSize = 300 / initialMoveCalls;
	FVector Directions[4] = { FVector(1,0,0), FVector(0,1,0), FVector(-1,0,0), FVector(0,-1,0) };
	short int keyPressed;
	FTimerHandle MemberTimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to move character
	void MovePawn();

	// Called to start moving character up
	void MoveUp();

	// Called to start moving character up
	void MoveRight();

	// Called to start moving character up
	void MoveDown();

	// Called to start moving character up
	void MoveLeft();

	// Called to intiate movement in current direction.
	void StartMove();

	// Called to stop character
	void StopPawn();

	// Rotate left
	void RotateLeft();

	// Rotate
	void RotateRight();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere)
		USpringArmComponent* OurCameraSpringArm;
	UCameraComponent* OurCamera;

};
