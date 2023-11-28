// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemySubsystem.h"
#include "InputAction.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

class UInputMappingContext;

UCLASS()
class SHOOTYMATH_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMapping;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> InputJump;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> InputMove;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> InputLook;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> InputShoot;
	
public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CameraSettings")
	TObjectPtr<class UCameraComponent> CameraComponent;

	UPROPERTY()
	UEnemySubsystem* EnemySubsystem;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);
	
	void Shoot(const FInputActionValue& Value);
};
