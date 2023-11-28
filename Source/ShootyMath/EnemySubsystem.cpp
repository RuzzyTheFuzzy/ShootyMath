// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySubsystem.h"

#include "FGGameplayMath/Intersection/IntersectionUtility.h"
#include "Intersection/IntersectionUtil.h"

void UEnemySubsystem::RegisterEnemy(UEnemyHitbox* EnemyHitbox)
{
	if (!EnemyHitboxes.Contains(EnemyHitbox))
	{
		EnemyHitboxes.Add(EnemyHitbox);
	}
}

void UEnemySubsystem::UnregisterEnemy(UEnemyHitbox* EnemyHitbox)
{
	if (EnemyHitboxes.Contains(EnemyHitbox))
		EnemyHitboxes.Remove(EnemyHitbox);
}

void UEnemySubsystem::RegisterCollider(UEnemyHitbox* EnemyHitbox)
{
	if (!ColliderHitboxes.Contains(EnemyHitbox))
	{
		ColliderHitboxes.Add(EnemyHitbox);
	}
}

void UEnemySubsystem::UnregisterCollider(UEnemyHitbox* EnemyHitbox)
{
	if (ColliderHitboxes.Contains(EnemyHitbox))
		ColliderHitboxes.Remove(EnemyHitbox);
}

bool UEnemySubsystem::RayIntersectionCheck(FVector Origin, FVector Direction)
{
	bool bHit = false;
	for (auto EnemyHitbox : EnemyHitboxes)
	{
		FVector Contactpoint;
		if (UIntersectionUtility::RayAABB(Origin, Direction, EnemyHitbox->Min + EnemyHitbox->GetComponentLocation(),
		                                  EnemyHitbox->Max + EnemyHitbox->GetComponentLocation(), Contactpoint))
		{
			bHit = true;
			EnemyHitbox->OnHit();
		}
	}

	return bHit;
}

void UEnemySubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (auto EnemyHitbox : EnemyHitboxes)
	{
		for (auto Collider : ColliderHitboxes)
		{
			FVector Contactpoint;
			if (EnemyHitbox && Collider)
			{
				if (UIntersectionUtility::AABBIntersect(EnemyHitbox->Min + EnemyHitbox->GetComponentLocation(),
				                                        EnemyHitbox->Max + EnemyHitbox->GetComponentLocation(),
				                                        Collider->Min + Collider->GetComponentLocation(),
				                                        Collider->Max + Collider->GetComponentLocation(), Contactpoint))
				{
					if (Collider->GetComponentLocation().Z + Collider->Max.Z < EnemyHitbox->GetComponentLocation().Z && EnemyHitbox->Velocity.Z < 0) // Should in theory not need to check the velocity but whatevs
					{
						EnemyHitbox->Velocity *= 0;
					}
				}
			}
		}
	}
}

TStatId UEnemySubsystem::GetStatId() const
{
	return GetStatID();
}
