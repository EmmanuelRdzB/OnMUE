// Copyright Epic Games, Inc. All Rights Reserved.

#include "OnMUECharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

#include "AbilitySystemComponent.h"
#include "Online/AOnMUEPlayerState.h"
#include "GameplayTagsManager.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "OnMUE.h"
#include "OnMUEPlayerController.h"
#include "Actors/OnMUEWC.h"
#include "GameFramework/PlayerState.h"


namespace
{
	const TCHAR* NetModeToString(const ENetMode NetMode)
	{
		switch (NetMode)
		{
		case NM_Standalone:
			return TEXT("Standalone");


		case NM_DedicatedServer:
			return TEXT("DedicatedServer");


		case NM_ListenServer:
			return TEXT("ListenServer");


		case NM_Client:
			return TEXT("Client");


		default:
			return TEXT("Unknown");
		}
	}
}


AOnMUECharacter::AOnMUECharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	// Create the first person mesh that will be viewed only by this character's owner
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));

	FirstPersonMesh->SetupAttachment(GetMesh());
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));

	// Create the Camera Component	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCameraComponent->SetupAttachment(FirstPersonMesh, FName("head"));
	FirstPersonCameraComponent->SetRelativeLocationAndRotation(FVector(-2.8f, 5.89f, 0.0f), FRotator(0.0f, 90.0f, -90.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
	FirstPersonCameraComponent->FirstPersonScale = 0.6f;

	// configure the character comps
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	GetCapsuleComponent()->SetCapsuleSize(34.0f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->AirControl = 0.5f;


	// Configure the WeaponComponent
	WeaponComponent =  CreateDefaultSubobject<UOnMUEWC>(TEXT("WeaponComponent"));

	// Get the saved tag in DeafultGameplaytag.ini
	SprintingTag = UGameplayTagsManager::Get().RequestGameplayTag(FName("State.Movement.Sprinting"));
}

FVector AOnMUECharacter::GetAimOrigin() const
{
	return GetPawnViewLocation(); //Returns the pawn location
}

FVector AOnMUECharacter::GetAimDirection() const
{
	return GetViewRotation().Vector(); //Returns the pawn ratation
}

void AOnMUECharacter::BeginPlay()
{
	Super::BeginPlay();


	const ENetMode NetMode = GetNetMode();


	const FString Label = FString::Printf(
		TEXT("%s | %s | Local=%s"),
		NetModeToString(NetMode),
		*UEnum::GetValueAsString(GetLocalRole()),
		IsLocallyControlled() ? TEXT("true") : TEXT("false")
	);


	if (NetMode != NM_DedicatedServer)
	{
		DrawDebugString(
			GetWorld(),
			FVector(0.0, 0.0, 120.0),
			Label,
			this,
			IsLocallyControlled() ? FColor::Green : FColor::Cyan,
			160.0f,
			true
		);
	}
}




void AOnMUECharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AOnMUECharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AOnMUECharacter::DoJumpEnd);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AOnMUECharacter::MoveInput);

		// Looking/Aiming
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AOnMUECharacter::LookInput);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AOnMUECharacter::LookInput);

		//Fire
		EnhancedInputComponent->BindAction(FireInput, ETriggerEvent::Triggered, this , &AOnMUECharacter::DoFire);

		//Sprint
		EnhancedInputComponent->BindAction(SprintInputAction, ETriggerEvent::Triggered, this, &AOnMUECharacter::StartSprinting);
		EnhancedInputComponent->BindAction(SprintInputAction, ETriggerEvent::Completed, this, &AOnMUECharacter::StopSprinting);

	}
	else
	{
		UE_LOG(LogOnMUE, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AOnMUECharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilityActorInfo();
	
}

void AOnMUECharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();

}

void AOnMUECharacter::InitAbilityActorInfo()
{

	AAOnMUEPlayerState* OnlinePS = GetPlayerState<AAOnMUEPlayerState>();

	if (OnlinePS)
	{
		// ASC

		UAbilitySystemComponent* ASC = OnlinePS->GetAbilitySystemComponent();
		if (ASC)
		{
			// Get Owner and Avatar
			ASC->InitAbilityActorInfo(OnlinePS, this);

			//AbilitySystemComponent =  ASC;
		}
	}

	
}


void AOnMUECharacter::MoveInput(const FInputActionValue& Value)
{
	// get the Vector2D move axis
	FVector2D MovementVector = Value.Get<FVector2D>();

	// pass the axis values to the move input
	DoMove(MovementVector.X, MovementVector.Y);

}

void AOnMUECharacter::LookInput(const FInputActionValue& Value)
{
	// get the Vector2D look axis
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// pass the axis values to the aim input
	DoAim(LookAxisVector.X, LookAxisVector.Y);

}

void AOnMUECharacter::DoAim(float Yaw, float Pitch)
{
	if (GetController())
	{
		// pass the rotation inputs
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AOnMUECharacter::DoMove(float Right, float Forward)
{
	if (GetController())
	{
		// pass the move inputs
		AddMovementInput(GetActorRightVector(), Right);
		AddMovementInput(GetActorForwardVector(), Forward);
	}
}

void AOnMUECharacter::DoJumpStart()
{
	// pass Jump to the character
	Jump();
}

void AOnMUECharacter::DoJumpEnd()
{
	// pass StopJumping to the character
	StopJumping();
}

 void AOnMUECharacter::DoFire()
{
	if (WeaponComponent)
	{
		WeaponComponent->TryStartFire();
	}
}

void AOnMUECharacter::StartSprinting()
{
	if (AAOnMUEPlayerState* OnlinePS = GetPlayerState<AAOnMUEPlayerState>())
	{
		if (UAbilitySystemComponent* ASC = OnlinePS->GetAbilitySystemComponent())
		{
			if (!HasStateTag(SprintingTag))
			{
				ASC->AddLooseGameplayTag(SprintingTag);
			}
		}
	}
}

void AOnMUECharacter::StopSprinting()
{
	if (AAOnMUEPlayerState* OnlinePS = GetPlayerState<AAOnMUEPlayerState>())
	{
		UAbilitySystemComponent* ASC = OnlinePS->GetAbilitySystemComponent();
		if (ASC)
		{
			ASC->RemoveLooseGameplayTag(SprintingTag);
		}
	}
}

bool AOnMUECharacter::HasStateTag(FGameplayTag TagToCheck) const
{
	if (AAOnMUEPlayerState* OnlinePS = GetPlayerState<AAOnMUEPlayerState>())
	{
			if (UAbilitySystemComponent* ASC = OnlinePS->GetAbilitySystemComponent())
			{
				return ASC->HasMatchingGameplayTag(TagToCheck);
			}
			return false;
	}
	return false;
}
