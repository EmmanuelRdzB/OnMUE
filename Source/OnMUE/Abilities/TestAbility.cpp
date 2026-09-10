// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/TestAbility.h"

// Sets default values
ATestAbility::ATestAbility()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestAbility::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

