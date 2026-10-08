// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UOnMUE_NetworkDiag.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ONMUE_API UUOnMUE_NetworkDiag : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUOnMUE_NetworkDiag();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void PrintNetworkRoles();

		
};
