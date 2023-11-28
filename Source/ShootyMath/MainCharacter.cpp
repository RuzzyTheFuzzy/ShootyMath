// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "EnemySubsystem.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "FGGameplayMath/Intersection/IntersectionSubsystem.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(RootComponent);

	CameraComponent->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	EnemySubsystem = GetWorld()->GetSubsystem<UEnemySubsystem>();
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController == nullptr)
		return;

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		PlayerController->GetLocalPlayer());

	if (Subsystem == nullptr)
		return;

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* PlayerEnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (PlayerEnhancedInput == nullptr)
		return;

	PlayerEnhancedInput->BindAction(InputJump, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	PlayerEnhancedInput->BindAction(InputJump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	PlayerEnhancedInput->BindAction(InputMove, ETriggerEvent::Triggered, this, &AMainCharacter::Move);
	PlayerEnhancedInput->BindAction(InputLook, ETriggerEvent::Triggered, this, &AMainCharacter::Look);
	PlayerEnhancedInput->BindAction(InputShoot, ETriggerEvent::Triggered, this, &AMainCharacter::Shoot);

	GetWorld()->GetSubsystem<UIntersectionSubsystem>()->RegisterPlayerController(PlayerController);
}

void AMainCharacter::Move(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		const FVector2d MoveDir = Value.Get<FVector2d>();
		const FRotator PlayerRotation(0, Controller->GetControlRotation().Yaw, 0);

		// Forward/Backward direction
		if (MoveDir.Y != 0.f)
		{
			// Get forward vector
			const FVector Direction = PlayerRotation.RotateVector(FVector::ForwardVector);

			AddMovementInput(Direction, MoveDir.Y);
		}

		// Right/Left direction
		if (MoveDir.X != 0.f)
		{
			// Get right vector
			const FVector Direction = PlayerRotation.RotateVector(FVector::RightVector);

			AddMovementInput(Direction, MoveDir.X);
		}
	}
}

void AMainCharacter::Look(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		const FVector2D LookDir = Value.Get<FVector2D>();

		if (LookDir.X != 0.f)
		{
			AddControllerYawInput(LookDir.X);
		}

		if (LookDir.Y != 0.f)
		{
			AddControllerPitchInput(LookDir.Y);
		}
	}
}

void AMainCharacter::Shoot(const FInputActionValue& Value)
{
	if (EnemySubsystem)
	{
		if (EnemySubsystem->RayIntersectionCheck(CameraComponent->GetComponentLocation(),
											CameraComponent->GetForwardVector()))
		{
			// On Hit on something
		}
	}
}
