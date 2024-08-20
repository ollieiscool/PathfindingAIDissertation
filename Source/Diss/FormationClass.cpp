// Fill out your copyright notice in the Description page of Project Settings.


#include "FormationClass.h"
#include "NavigationSystem.h"

UFormationClass::UFormationClass() {

}

UFormationClass::~UFormationClass() {

}

//Adds a new position on alternating sides of the MouseHitLocation based on the length of the line and unit offset
void UFormationClass::GetLinePositions(TArray<FVector>& FormationPos, TArray<APositionInFormation*> Positions, FVector MouseHitLocation, int NumOfUnitsSelected, int LengthOfLine, float UnitOffset, FRotator CameraRotation, bool IsMoving) {
	float x = 0;
	float y = UnitOffset;
	FVector FirstPos;
	FVector NextPos;
	
	FirstPos = MouseHitLocation;

	for (int i = 0; i < NumOfUnitsSelected; i++) {
		if (i % LengthOfLine == 0 && i != 0) {
			y = 0;
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
			y += UnitOffset;
		}
	}
}

void UFormationClass::DragLine(TArray<FVector>& FormationPos, FVector MouseHitLocation, int NumOfUnitsSelected, int LengthOfLine, float UnitOffset, FRotator LineRotation) {
	float x = 0;
	float y = UnitOffset;
	FVector FirstPos;
	FVector NextPos;

	FirstPos = MouseHitLocation;
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

void UFormationClass::GetSquarePositions(TArray<FVector>& FormationPos, TArray<APositionInFormation*> Positions, FVector MouseHitLocation, int NumOfUnitsSelected, float UnitOffset, FRotator CameraRotation, bool IsMoving) {
	float x = 0;
	float y = UnitOffset;
	FVector FirstPos;
	FVector NextPos;
	TArray<double> Squares = FindSquares(1, 200);

	FirstPos = MouseHitLocation;
	double LineLength;

	if (IsSquare(double(NumOfUnitsSelected)) == true) {
		LineLength = FMath::Sqrt(double(NumOfUnitsSelected));
	}
	else {
		for (int i = 0; i < Squares.Num(); i++) {
			if (NumOfUnitsSelected < Squares[i]) {
				LineLength = FMath::Sqrt(Squares[i - 1]);
			}
		}
	}

	for (int i = 0; i < NumOfUnitsSelected; i++) {
		if (i % int(LineLength) == 0 && i != 0) {
			y = 0;
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
			y += UnitOffset;
		}
	}
	
}

void UFormationClass::DragSquare(TArray<FVector>& FormationPos, FVector MouseHitLocation, int NumOfUnitsSelected, int LengthOfLine, float UnitOffset, FRotator LineRotation) {
	float x = 0;
	float y = UnitOffset;
	FVector FirstPos;
	FVector NextPos;

	TArray<double> Squares = FindSquares(1, 200);
	double LineLength;

	if (IsSquare(double(NumOfUnitsSelected)) == true) {
		LineLength = FMath::Sqrt(double(NumOfUnitsSelected));
	}
	else {
		for (int i = 0; i < Squares.Num(); i++) {
			if (NumOfUnitsSelected < Squares[i]) {
				LineLength = FMath::Sqrt(Squares[i - 1]);
			}
		}
	}

	FirstPos = MouseHitLocation;
	int ModNum = (LengthOfLine + int(LineLength)) - 1;
	for (int i = 0; i < NumOfUnitsSelected; i++) {
		if (i % ModNum == 0 && i != 0) {
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

void UFormationClass::GetDiamondPositions(TArray<FVector>& FormationPos, TArray<APositionInFormation*> Positions, FVector MouseHitLocation, int NumOfUnitsSelected, int LengthOfLine, float UnitOffset, FRotator CameraRotation, bool IsMoving) {

}

void UFormationClass::DragDiamond(TArray<FVector>& FormationPos, FVector MouseHitLocation, int NumOfUnitsSelected, int LengthOfLine, float UnitOffset, FRotator LineRotation) {

}

bool UFormationClass::IsSquare(double x) {
	if (x >= 0) {
		double SquareRoot = FMath::Sqrt(x);
		return (SquareRoot * SquareRoot == x);
	}
	return false;
}

TArray<double> UFormationClass::FindSquares(double min, double max) {
	TArray<double> Squares;
	for (double i = min; i <= max; i++) {
		if (IsSquare(i)) {
			Squares.Add(i);
		}
	}
	return Squares;
}

