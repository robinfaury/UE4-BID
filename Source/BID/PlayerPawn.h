// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EngineMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "PlayerPawn.generated.h"
 
UCLASS()
class BID_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	UPROPERTY(EditAnywhere)
	UCameraComponent* PlayerCamera;

	TWeakObjectPtr <AActor> grabbedObject;

	void GrabObject(AActor* other);

	void MoveX(float amount);
	void MoveY(float amount);
	void MoveDownUp(float amount);
	void DoAction();

	TWeakObjectPtr <AActor> touchedActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
