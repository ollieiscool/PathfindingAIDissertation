// Fill out your copyright notice in the Description page of Project Settings.


#include "FormationClass.h"
#include "NavigationSystem.h"

UFormationClass::UFormationClass() {

}

UFormationClass::~UFormationClass() {

}

//Adds a new position on alternating sides of the MouseHitLocation based on the length of the line and unit offset
void UFormationClass::GetPositions(TArray<FVector>& FormationPos, TArray<APositionInFormation*> Positions, FVector MouseHitLocation, int NumOfUnitsSelected, int LengthOfLine, float UnitOffset, FRotator CameraRotation, bool IsMoving) {
	float x = 0;
	float y = UnitOffset;
	FVector FirstPos;
	FVector NextPos;
	FNavLocation NavLoc;
	FVector Extent(500, 500, 10000);
	
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

void UFormationClass::DragLine(TArray<FVector>& FormationPos, FVector MouseHitLocation, int NumOfUnitsSelected, int LengthOfLine, float UnitOffset, FRotator LineRotation) {
	float x = 0;
	float y = UnitOffset;
	FVector FirstPos;
	FVector NextPos;

	FirstPos = MouseHitLocation;
	PreviousHitLocation = MouseHitLocation;
	for (int i = 0; i < NumOfUnitsSelected; i++) {
		if (i % LengthOfLine == 0 && i != 0) {
			y = 0;
			x -= UnitOffset;
			
		}
		NextPos = LineRotation.RotateVector(FVector(x, y, 0));

		if (i == 0) {
			FormationPos.Add(FirstPos);
		}
		else {
			FormationPos.Add(FirstPos + NextPos);
			y += UnitOffset;
		}
	}
}

FVector UFormationClass::Find8thOfWay(FVector TargetPosition, FVector CurrentPos) {
	return (TargetPosition - CurrentPos) / 8;
}
