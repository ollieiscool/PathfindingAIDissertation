// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PositionInFormation.h"
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

	UFUNCTION(Category = "Formation Navigation")
	TArray<FVector> GetPositions(FVector MouseHitLocation, int NumOfUnitsSelected, int LengthOfLine = 5, float UnitOffset = 80);

	UFUNCTION(BlueprintCallable, Category = "Formation Navigation")
	void MoveExistingFormation(TArray<APositionInFormation*> Positions, FVector MouseHitLocation, int LengthOfLine, float UnitOffset);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Formation Navigation")
	FVector PreviousHitLocation;
};