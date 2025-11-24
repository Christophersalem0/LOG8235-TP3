// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GoToBestCollectible.h"
#include "SoftDesignTraining/SDTAIController.h"
#include "SoftDesignTraining/AI/SoftDesignAIController.h"

#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"


EBTNodeResult::Type UBTTask_GoToBestCollectible::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner())) {
		aiController->MoveToRandomCollectible();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

