// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "EnemyHitbox.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class SHOOTYMATH_API UEnemyHitbox : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyHitbox();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="AABB", meta = (MakeEditWidget = true))
	FVector Min;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="AABB", meta = (MakeEditWidget = true))
	FVector Max;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="AABB")
	bool bIsEnemy;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Physics2")
	FVector Gravity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Physics2")
	FVector StartingImpulse;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Physics2")
	FVector LinearFriction;
	
	
	FVector Velocity;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnHit();

		
};
