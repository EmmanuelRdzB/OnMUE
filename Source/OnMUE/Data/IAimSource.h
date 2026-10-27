// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IAimSource.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI)
class UAimSource : public UInterface
{
	GENERATED_BODY()
};

class ONMUE_API IAimSource
{
	GENERATED_BODY()
public:
	IAimSource();

	//Get the owned pawn location location
	virtual FVector GetAimOrigin() const = 0;

	//Get the owned pawn rotation
	virtual FVector GetAimDirection() const = 0;

	
};
