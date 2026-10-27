// Fill out your copyright notice in the Description page of Project Settings.


#include "Online/AOnMUEPlayerState.h"

#include "UOnlineAttributeSet.h"

AAOnMUEPlayerState::AAOnMUEPlayerState()
{
	//Replicar el player state
	bReplicates = true;
	SetNetUpdateFrequency(100.0f);

	//Create Subobject Ability system component
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	//Create Subobject Attribute Set
	AttributeSet = CreateDefaultSubobject<UUOnlineAttributeSet>(TEXT("OnlineAttributeSet"));

	//replicated Settings ASC

	AbilitySystemComponent->SetIsReplicated(true);

	//Get a replicated mode for human Players

	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* AAOnMUEPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}




