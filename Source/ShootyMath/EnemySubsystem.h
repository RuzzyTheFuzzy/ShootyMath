// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyHitbox.h"
#include "Subsystems/WorldSubsystem.h"
#include "EnemySubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTYMATH_API UEnemySubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<UEnemyHitbox*> EnemyHitboxes;

	UPROPERTY()
	TArray<UEnemyHitbox*> ColliderHitboxes;

public:
	void RegisterEnemy(UEnemyHitbox* EnemyHitbox);
	void UnregisterEnemy(UEnemyHitbox* EnemyHitbox);
	void RegisterCollider(UEnemyHitbox* EnemyHitbox);
	void UnregisterCollider(UEnemyHitbox* EnemyHitbox);
	bool RayIntersectionCheck(FVector Origin, FVector Direction);

	virtual void Tick(float DeltaTime) override;

	virtual TStatId GetStatId() const override;
};
