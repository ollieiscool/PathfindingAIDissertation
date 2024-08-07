// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PositionInFormation.generated.h"

UCLASS()
class DISS_API APositionInFormation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APositionInFormation();

	UFUNCTION(BlueprintCallable, Category = "Formation Navigation")
	bool GetIsReserved() {
		return IsReserved;
	};

	UFUNCTION(BlueprintCallable, Category = "Formation Navigation")
	void SetIsReserved(bool NewIsReserved) {
		IsReserved = NewIsReserved;
	};

	UFUNCTION(BlueprintCallable, Category = "Formation Navigation")
	FVector GetPosition() {
		return Position;
	};

	UFUNCTION(BlueprintCallable, Category = "Formation Navigation")
	void SetPosition(FVector NewPosition) {
		Position = NewPosition;
	};
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Formation Navigation")
	bool IsReserved;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Formation Navigation")
	FVector Position;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
