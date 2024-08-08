// Copyright Epic Games, Inc. All Rights Reserved.

#include "DissPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "DissCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "RTSUnit.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ADissPlayerController::ADissPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;

	formation = NewObject<UFormationClass>();
}

void ADissPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void ADissPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ADissPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ADissPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ADissPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ADissPlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &ADissPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &ADissPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &ADissPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &ADissPlayerController::OnTouchReleased);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ADissPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void ADissPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void ADissPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void ADissPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void ADissPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

//Unit Nav and formation logic, Oliver Perrin
void ADissPlayerController::DrawFormation(const TArray<AActor*>& SelectedUnits) {
	FormationPos = formation->GetPositions(MouseHitLocation, SelectedUnits.Num(), 6, 80);

	APositionInFormation* NewPos;
	for (int i = 0; i < FormationPos.Num(); i++) {
		NewPos = NewObject<APositionInFormation>();
		NewPos->SetPosition(FormationPos[i]);
		Positions.Add(NewPos);
	}
	
	//Spawns instances of the RTSUnit class to visualise formation, TESTING ONLY
	//for (int i = 0; i < FormationPos.Num(); i++) {
	//	FActorSpawnParameters SpawnInfo;
	//	GetWorld()->SpawnActor<AActor>(actorToSpawn, FormationPos[i], FRotator(0, 0, 0), SpawnInfo);
	//}
}

APositionInFormation* ADissPlayerController::FindClosestPoint(FVector CurrentPos) {
	float ShortestDist = 1000000000000.0;
	float CurrentDist;
	int ClosestPos = 0;

	if (Positions.Num() > 0) {
		for (int i = 0; i < Positions.Num(); i++) {
			CurrentDist = FVector::Distance(Positions[i]->GetPosition(), CurrentPos);
			
			if (CurrentDist < ShortestDist && Positions[i]->GetIsReserved() == false) {
				ShortestDist = CurrentDist;
				ClosestPos = i;
			}
		}
		
		if (Positions[ClosestPos] != 0) {
			Positions[ClosestPos]->SetIsReserved(true);
			return Positions[ClosestPos];
		}
		else {
			return 0;
		}
		
	}
	else {
		return 0;
	}
}

TArray<AActor*> ADissPlayerController::SortSelectedUnitsArray(const TArray<AActor*>& SelectedUnits) {
	TArray<AActor*> SortedArray;
	TMap<int, float> Distances;
	float DistFromMouseHit;

	if (SelectedUnits.Num() > 0) {
		for (int i = 0; i < SelectedUnits.Num(); i++) {
			DistFromMouseHit = FVector::Distance(MouseHitLocation, (SelectedUnits[i])->GetActorLocation());
			Distances.Add(i, DistFromMouseHit);
		}
		Distances.ValueSort([](float a, float b){
			return a > b;
		});

		for (auto& Elem : Distances) {
			SortedArray.Add(SelectedUnits[Elem.Key]);
		}
		return SortedArray;
	}
	else {
		return SortedArray;
	}
}

void ADissPlayerController::MoveFormation() {
	formation->MoveExistingFormation(Positions, MouseHitLocation, 6, 80);
	for (int i = 0; i < Positions.Num(); i++) {
		Positions[i]->SetIsReserved(false);
		IsMoving = true;
	}
}

void ADissPlayerController::MovePositionsTowardsTarget(float dt) {
	int SuccessfulTranslations = 0;
	for (int i = 0; i < Positions.Num(); i++) {
		FVector Direction = Positions[i]->GetTargetPosition() - Positions[i]->GetPosition();
		Direction.Normalize();
		if (Positions[i]->GetPosition() != Positions[i]->GetTargetPosition()) {
			Positions[i]->SetPosition(Positions[i]->GetPosition() + (Direction * dt * 1000));
		}
		else if (Positions[i]->GetPosition() == Positions[i]->GetTargetPosition()) {
			SuccessfulTranslations += 1;
		}
	}
	if (SuccessfulTranslations == Positions.Num()) {
		IsMoving = false;
	}
}

void ADissPlayerController::ClearPositionsArray() {
	Positions.Empty();
}