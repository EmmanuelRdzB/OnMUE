// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthC.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDamage);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ONMUE_API UHealthC : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthC();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Health")
	float MaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Health")
	float CurrentHealth;

	
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, Category="Health")
	FOnDamage OnDamage;

	UFUNCTION(BlueprintCallable, Category="Health")
	void OnDamageRecieved();
};
