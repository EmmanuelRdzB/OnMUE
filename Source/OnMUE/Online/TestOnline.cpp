// Fill out your copyright notice in the Description page of Project Settings.


#include "Online/TestOnline.h"

// Sets default values
ATestOnline::ATestOnline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestOnline::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestOnline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

