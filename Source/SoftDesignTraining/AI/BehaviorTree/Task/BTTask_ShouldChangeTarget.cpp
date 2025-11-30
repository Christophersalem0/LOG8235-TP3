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
        if (aiController->AtJumpSegment) {
            //DrawDebugSphere(GetWorld(), aiController->GetPawn()->GetActorLocation() + FVector(0.f, 0.f, 100.f), 15.0f, 32, FColor::Green);
            return EBTNodeResult::Failed;
        }
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
        //DrawDebugSphere(GetWorld(), aiController->GetPawn()->GetActorLocation() + FVector(0.f, 0.f, 100.f), 15.0f, 32, FColor::Red);
    }

    return EBTNodeResult::Failed;
}

