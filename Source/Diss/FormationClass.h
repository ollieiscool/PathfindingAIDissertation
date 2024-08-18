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
	void GetPositions(TArray<FVector>& FormationPos, TArray<APositionInFormation*> Positions, FVector MouseHitLocation, int NumOfUnitsSelected, int LengthOfLine = 5, float UnitOffset = 80, FRotator CameraRotation = FRotator(0,0,0), bool IsMoving = false);

	UFUNCTION(BlueprintCallable, Category = "Formation Navigation")
	void DragLine(TArray<FVector>& FormationPos, FVector MouseHitLocation, int NumOfUnitsSelected, int LengthOfLine, float UnitOffset, FRotator LineRotation);

	UFUNCTION(Category = "Formation Navigation")
	FVector Find8thOfWay(FVector TargetPosition, FVector CurrentPos);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Formation Navigation")
	FVector PreviousHitLocation;
};