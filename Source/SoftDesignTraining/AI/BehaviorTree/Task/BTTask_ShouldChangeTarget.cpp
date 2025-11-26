// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ShouldChangeTarget.h"

#include "SoftDesignTraining/SoftDesignTraining.h"
#include "SoftDesignTraining/SDTAIController.h"
#include "SoftDesignTraining/AI/SoftDesignAIController.h"

#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"


EBTNodeResult::Type UBTTask_ShouldChangeTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {
        if (aiController->InAir)
            return EBTNodeResult::Failed;
        if (OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Bool>(aiController->GetTargetSeenKeyID()))
        {
            return EBTNodeResult::Succeeded;
        }
        if (aiController->m_ReachedTarget) {
            return EBTNodeResult::Succeeded;
        }
        if (OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Bool>(aiController->GetIsInGroupKeyID())) {
            return EBTNodeResult::Succeeded;
        }
    }
    return EBTNodeResult::Failed;
}

