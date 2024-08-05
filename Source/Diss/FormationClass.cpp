// Fill out your copyright notice in the Description page of Project Settings.


#include "FormationClass.h"

UFormationClass::UFormationClass() {

}

UFormationClass::~UFormationClass() {

}

TArray<FVector> UFormationClass::GetPositions(FVector MouseHitLocation, int NumOfUnitsSelected, int LengthOfLine) {
	TArray<FVector> FormationPositions;
	float x = 0;
	float y = 80;
	FVector FirstPos;
	FVector NextPos;
	
	FirstPos = MouseHitLocation;
	for (int i = 0; i < NumOfUnitsSelected; i++) {
		if (i % LengthOfLine == 0 && i != 0) {
			y -= y;
			x -= 80;
		}

		NextPos = FVector(x, y, 0);

		if (i == 0) {
			FormationPositions.Add(FirstPos);
		}
		else {
			FormationPositions.Add(FirstPos + NextPos);
			if (i % 2 == 0) {
				y -= 80;
			}
			y *= -1;
		}
	}
	return FormationPositions;
}