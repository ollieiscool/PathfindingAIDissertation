// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "FormationClass.h"
#include "RTSUnit.h"
#include "DissPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class ADissPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADissPlayerController();

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationClickAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationTouchAction;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();

	//Unit Navigation and formation logic, Oliver Perrin.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DissRTSController, meta = (AllowPrivateAccess = "true"))
	FVector MouseHitLocation;

	UFormationClass* formation;

	UFUNCTION(BlueprintCallable, Category = "Formation Navigation")
	void DrawFormation(const TArray<AActor*>& SelectedUnits);

	UFUNCTION(BlueprintCallable, Category = "Formation Navigation")
	FVector FindClosestPoint(FVector CurrentPos);

	UFUNCTION(BlueprintCallable, Category = "Formation Navigation")
	TArray<AActor*> SortSelectedUnitsArray(const TArray<AActor*>& SelectedUnits);

	UPROPERTY(EditAnywhere)
	 TSubclassOf<AActor> actorToSpawn;

	 UPROPERTY(EditAnywhere)
	 TArray<FVector> FormationPos;

private:
	FVector CachedDestination;

	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed
};

