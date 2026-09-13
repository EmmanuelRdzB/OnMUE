// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AOnMUEGameState.generated.h"

/**
 * 
 */
UCLASS()
class ONMUE_API AAOnMUEGameState : public AGameStateBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
};
