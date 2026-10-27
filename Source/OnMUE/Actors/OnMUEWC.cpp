// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/OnMUEWC.h"
#include "../Data/IAimSource.h"
#include "../Data/WeaponData.h"

// Sets default values for this component's properties
UOnMUEWC::UOnMUEWC()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UOnMUEWC::TryStartFire()
{
	if (!WeaponDefinition) return;

	//Serch for the owner
	if (IAimSource* AimInterface = Cast<IAimSource>(GetOwner()))
	{
		FVector Origin = AimInterface->GetAimOrigin();
		FVector Direction = AimInterface->GetAimDirection();

		FString TypeStr = (WeaponDefinition->WeaponType == EWeaponType::Hitscan) ? TEXT("Hitscan") : TEXT("Projectile");

		UE_LOG(LogTemp, Warning, TEXT("Weapon name : %s | Type : %s | Damage : %f | Origin %s"), *WeaponDefinition->WeaponName.ToString(), *TypeStr, WeaponDefinition->BaseDamage, *Origin.ToString());
	}
	
}

// Called when the game starts
void UOnMUEWC::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UOnMUEWC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

