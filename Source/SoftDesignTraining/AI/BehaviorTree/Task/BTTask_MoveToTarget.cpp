// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToTarget.h"
#include "SoftDesignTraining/SoftDesignTraining.h"
#include "SoftDesignTraining/SDTAIController.h"
#include "SoftDesignTraining/AI/SoftDesignAIController.h"

#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"


EBTNodeResult::Type UBTTask_MoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {
        FVector3d vector = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Vector>(aiController->GetTargetPosBBKeyID());
        //aiController->MoveToLocation(aiController->target, 0.5f, false, true, false, false, NULL, false);
        //aiController->OnMoveToTarget();
        aiController->MoveToLKP();
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}

