// Fill out your copyright notice in the Description page of Project Settings.


#include "FormationClass.h"

UFormationClass::UFormationClass() {

}

UFormationClass::~UFormationClass() {

}

TArray<FVector> UFormationClass::GetPositions(FVector MouseHitLocation, int NumOfUnitsSelected) {
	TArray<FVector> FormationPositions;
	FVector FirstPos;
	FVector NextPos = FVector(0, 200, 0);
	
	FirstPos = MouseHitLocation;
	for (int i = 0; i < NumOfUnitsSelected; i++) {
		FormationPositions.Add(FirstPos);
		FirstPos += NextPos;
	}
	return FormationPositions;
}