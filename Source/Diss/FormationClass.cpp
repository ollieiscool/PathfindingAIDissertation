// Fill out your copyright notice in the Description page of Project Settings.


#include "FormationClass.h"

UFormationClass::UFormationClass() {

}

UFormationClass::~UFormationClass() {

}

//Adds a new position on alternating sides of the MouseHitLocation based on the length of the line and unit offset
TArray<FVector> UFormationClass::GetPositions(FVector MouseHitLocation, int NumOfUnitsSelected, int LengthOfLine, float UnitOffset) {
	TArray<FVector> FormationPositions;
	float x = 0;
	float y = UnitOffset;
	FVector FirstPos;
	FVector NextPos;
	
	FirstPos = MouseHitLocation;
	PreviousHitLocation = MouseHitLocation;
	for (int i = 0; i < NumOfUnitsSelected; i++) {
		if (i % LengthOfLine == 0 && i != 0) {
			y -= y;
			x -= UnitOffset;
		}

		NextPos = FVector(x, y, 0);

		if (i == 0) {
			FormationPositions.Add(FirstPos);
		}
		else {
			FormationPositions.Add(FirstPos + NextPos);
			if (i % 2 == 0) {
				y -= UnitOffset;
			}
			y *= -1;
		}
	}
	return FormationPositions;
}

void UFormationClass::MoveExistingFormation(TArray<APositionInFormation*> Positions, FVector MouseHitLocation, int LengthOfLine, float UnitOffset) {
	float x = 0;
	float y = UnitOffset;
	FVector FirstPos;
	FVector NextPos;

	FirstPos = MouseHitLocation;
	for (int i = 0; i < Positions.Num(); i++) {
		if (i % LengthOfLine == 0 && i != 0) {
			y -= y;
			x -= UnitOffset;
		}

		NextPos = FVector(x, y, 0);

		if (i == 0) {
			Positions[i]->SetTargetPosition(FirstPos);
		}
		else {
			Positions[i]->SetTargetPosition(FirstPos + NextPos);
			if (i % 2 == 0) {
				y -= UnitOffset;
			}
			y *= -1;
		}
	}
}
