// Fill out your copyright notice in the Description page of Project Settings.


#include "FormationClass.h"
#include "NavigationSystem.h"

UFormationClass::UFormationClass() {

}

UFormationClass::~UFormationClass() {

}

//Adds a new position on alternating sides of the MouseHitLocation based on the length of the line and unit offset
void UFormationClass::GetPositions(TArray<FVector>& FormationPos, TArray<APositionInFormation*> Positions, FVector MouseHitLocation, int NumOfUnitsSelected, int LengthOfLine, float UnitOffset, FRotator CameraRotation, bool IsMoving) {
	//UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	//TArray<FVector> FormationPositions;
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

		NextPos = CameraRotation.RotateVector(FVector(x, y, 0));

		if (i == 0) {
			if (IsMoving == false) {
				FormationPos.Add(FirstPos);
			}
			else {
				Positions[i]->SetPosition(FirstPos);
			}
		}
		else {
			if (IsMoving == false) {
				FormationPos.Add(FirstPos + NextPos);
			}
			else {
				Positions[i]->SetPosition(FirstPos + NextPos);
			}
			
			if (i % 2 == 0) {
				y -= UnitOffset;
			}
			y *= -1;
		}
	}
}

TArray<FVector> UFormationClass::DragLine(FVector MouseHitLocation, int NumOfUnitsSelected, int LengthOfLine, float UnitOffset, FRotator LineRotation) {
	float x = 0;
	float y = UnitOffset;
	FVector FirstPos;
	FVector NextPos;
	TArray<FVector> Positions;
	bool StartLine = true;

	FirstPos = MouseHitLocation;
	PreviousHitLocation = MouseHitLocation;
	for (int i = 0; i < NumOfUnitsSelected; i++) {
		if (y > UnitOffset * LengthOfLine) {
			y = UnitOffset;
			x -= UnitOffset;
			StartLine = true;
		}
		NextPos = LineRotation.RotateVector(FVector(x, y, 0));

		if (StartLine == true) {
			Positions.Add(FirstPos);
			StartLine = false;
		}
		else {
			Positions.Add(FirstPos + NextPos);
			y += UnitOffset;
		}
	}
	return Positions;
}

FVector UFormationClass::Find8thOfWay(FVector TargetPosition, FVector CurrentPos) {
	return (TargetPosition - CurrentPos) / 8;
}
