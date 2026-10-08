// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/UOnMUE_NetworkDiag.h"

// Sets default values for this component's properties
UUOnMUE_NetworkDiag::UUOnMUE_NetworkDiag()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUOnMUE_NetworkDiag::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UUOnMUE_NetworkDiag::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UUOnMUE_NetworkDiag::PrintNetworkRoles()
{
		AActor* MyOwner = GetOwner();

	if (MyOwner)
	{
		ENetMode NetMode = MyOwner->GetNetMode();
		ENetRole LocalRole = MyOwner->GetLocalRole();
		ENetRole RemoteRole = MyOwner->GetRemoteRole();

		FString NetModeString = (NetMode == NM_Client) ? TEXT("Client") : TEXT("Server");

		//PRINT LOG
		UE_LOG(LogTemp, Warning, TEXT("%s Actor : %s | Local Role : %d | Remote Role : %d"), *NetModeString, *MyOwner->GetName(), LocalRole, RemoteRole);
		
	}
}

