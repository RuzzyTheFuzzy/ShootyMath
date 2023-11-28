// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHitbox.h"

#include "EnemySubsystem.h"

// Sets default values for this component's properties
UEnemyHitbox::UEnemyHitbox()
{
	PrimaryComponentTick.bCanEverTick = true;

	bIsEnemy = true;

	// ...
}


// Called when the game starts
void UEnemyHitbox::BeginPlay()
{
	Super::BeginPlay();

	const auto SubSystem = GetWorld()->GetSubsystem<UEnemySubsystem>();
	if (bIsEnemy)
	{
	SubSystem->RegisterEnemy(this);
	}else
	{
		SubSystem->RegisterCollider(this);
	}

	Velocity = StartingImpulse;
}


// Called every frame
void UEnemyHitbox::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsEnemy)
	{
		auto Owner = GetOwner();

		auto Location = Owner->GetActorLocation();

		FVector NewLocation = Location + Velocity * DeltaTime;

		Owner->SetActorLocation(NewLocation);

		Velocity *= LinearFriction;

		Velocity += Gravity;
	}


	// ...
}
