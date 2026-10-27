// Fill out your copyright notice in the Description page of Project Settings.


#include "Online/UOnlineAttributeSet.h"
#include "Net/UnrealNetwork.h"


UUOnlineAttributeSet::UUOnlineAttributeSet()
{
	InitHealth(100.0f);

	InitMaxHealth(200.0f);

	InitStamina(100.0f);
}

void UUOnlineAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UUOnlineAttributeSet, Health, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UUOnlineAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UUOnlineAttributeSet, Stamina, COND_None, REPNOTIFY_Always);

}

void UUOnlineAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{

	GAMEPLAYATTRIBUTE_REPNOTIFY(UUOnlineAttributeSet, Health, OldHealth)
	
}

void UUOnlineAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUOnlineAttributeSet, MaxHealth, OldMaxHealth)
}

void UUOnlineAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUOnlineAttributeSet, Stamina, OldStamina)
}



