// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FormationClass.generated.h"

/**
 * 
 */
UCLASS()
class DISS_API UFormationClass : public UObject
{
	GENERATED_BODY()
	
public:
	UFormationClass();

	~UFormationClass();

	UFUNCTION(Category = "AI")
	TArray<FVector> GetPositions(FVector MouseHitLocation, int NumOfUnitsSelected);
};