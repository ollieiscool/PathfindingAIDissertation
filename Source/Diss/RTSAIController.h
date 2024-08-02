// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RTSAIController.generated.h"

/**
 * 
 */
UCLASS()
class DISS_API ARTSAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ARTSAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;

};
