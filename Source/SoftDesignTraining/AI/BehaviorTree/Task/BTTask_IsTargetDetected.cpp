// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_IsTargetDetected.h"
#include "SoftDesignTraining/SoftDesignTraining.h"
#include "SoftDesignTraining/SDTAIController.h"
#include "SoftDesignTraining/AI/SoftDesignAIController.h"

#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"


EBTNodeResult::Type UBTTask_IsTargetDetected::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (ASoftDesignAIController* aiController = Cast<ASoftDesignAIController>(OwnerComp.GetAIOwner()))
    {
        if (OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Bool>(aiController->GetTargetSeenKeyID())
            || OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Bool>(aiController->GetIsInGroupKeyID()))
        {
            return EBTNodeResult::Succeeded;
        }
    }

    return EBTNodeResult::Failed;
}