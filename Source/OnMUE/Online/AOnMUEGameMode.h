// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AOnMUEGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ONMUE_API AAOnMUEGameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
};
