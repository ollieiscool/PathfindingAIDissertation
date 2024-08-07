// Fill out your copyright notice in the Description page of Project Settings.


#include "PositionInFormation.h"

// Sets default values
APositionInFormation::APositionInFormation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IsReserved = false;
}

// Called when the game starts or when spawned
void APositionInFormation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APositionInFormation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

