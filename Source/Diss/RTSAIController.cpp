// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSAIController.h"
#include "RTSUnit.h"

//ARTSAIController::ARTSAIController(FObjectInitializer, const& ObjectInitializer) {

//}

void ARTSAIController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);
	/*if (ARTSUnit* const unit = Cast<ARTSUnit>(InPawn)) {
		if (UBehaviorTree* const tree = unit->GetBehaviourTree()) {
			UBlackboardComponent* b;
			UseBlackboard(tree->BlackboardAsset, [&]b);
			Blackboard = b;
			RunBehaviorTree(tree);
		}
	}*/
}