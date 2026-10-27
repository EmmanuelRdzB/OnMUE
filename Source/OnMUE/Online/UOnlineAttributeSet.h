// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"

#include "AbilitySystemComponent.h"

#include "UOnlineAttributeSet.generated.h"

/**
 * 
 */

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)\
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class ONMUE_API UUOnlineAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UUOnlineAttributeSet();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//Health Attribute

	UPROPERTY(ReplicatedUsing = OnRep_Health, BlueprintReadOnly, category = " Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UUOnlineAttributeSet, Health)

	UPROPERTY(ReplicatedUsing = OnRep_MaxHealth, BlueprintReadOnly, category = "attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UUOnlineAttributeSet, MaxHealth)

	UPROPERTY(ReplicatedUsing = OnRep_Stamina, BlueprintReadOnly, category = "attributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UUOnlineAttributeSet, Stamina)

protected:

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	UFUNCTION()
	virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina);
	
};
