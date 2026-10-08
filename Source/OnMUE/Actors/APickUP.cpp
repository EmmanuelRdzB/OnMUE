// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BoxComponent.h"
#include "Actors/APickUP.h"

// Sets default values
AAPickUP::AAPickUP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Component Instance
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("CollisionBox"));

	//Give it a size
	BoxCollision->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	//Set collision preset
	BoxCollision->SetCollisionProfileName(FName("OverlapAllDynamic"));

	//Attach it as the root
	RootComponent = BoxCollision;

	//Tells if this Actor will be replicated
	bReplicates = true;
}

// Called when the game starts or when spawned
void AAPickUP::BeginPlay()
{
	Super::BeginPlay();

	//Usamos authority
	if (HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("Servidor: Se creo el cartucho %s en el mundo"),*GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cliente: Recibido la replicacion del cartucho %s en el mundo"),*GetName());
	}
}

// Called every frame
void AAPickUP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAPickUP::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAPickUP, bIsAvailable);
	DOREPLIFETIME(AAPickUP, CurrentAmmo);
}

void AAPickUP::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AOnMUECharacter* ACharacter = Cast<AOnMUECharacter>(OtherActor);

	if (ACharacter && HasAuthority())
	{
		bIsAvailable = false;
		int32 OldAmmo = CurrentAmmo;
		CurrentAmmo = 10;

		SetActorHiddenInGame(true);

		SetActorEnableCollision(false);

		SetLifeSpan(5.0f);

		//Old Value from my replicated property
		OnRep_SetAmmoParticles(OldAmmo);
	}
}

void AAPickUP::OnRep_SetAmmoParticles(int32 OldAmmo)
{
	FString NewAmmo = HasAuthority() ? TEXT("SERVER") : TEXT("CLIENT");
	UE_LOG(LogTemp, Warning, TEXT("%s Actor: OLDAMMO: %d | CURRRENT AMMO: %d"), *NewAmmo, OldAmmo, CurrentAmmo);
}
