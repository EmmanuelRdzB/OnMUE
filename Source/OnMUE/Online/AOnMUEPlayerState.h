// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"

//Ability System Component (GAS)
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"

#include "AOnMUEPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class ONMUE_API AAOnMUEPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAOnMUEPlayerState();

	//Implementamos la interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS | Components")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS | Attributes")
	TObjectPtr<class UUOnlineAttributeSet> AttributeSet;
	
};
