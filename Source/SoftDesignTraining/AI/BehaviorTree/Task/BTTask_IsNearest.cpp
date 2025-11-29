// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_IsNearest.h"
#include "SoftDesignTraining/SDTAIController.h"
#include <SoftDesignTraining/AiAgentGroupManager.h>

EBTNodeResult::Type UBTTask_IsNearest::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (ASDTBaseAIController* aiController = Cast<ASDTBaseAIController>(OwnerComp.GetAIOwner()))
    {
        if (AiAgentGroupManager::GetInstance()->IsNearestToPlayer(aiController))
        {
            DrawDebugString(GetWorld(), FVector(0.f, 0.f, 10.f), "JLE RUSH", aiController->GetPawn(), FColor::Red, 5.f, false);

            return EBTNodeResult::Succeeded;
        }
    }

    return EBTNodeResult::Failed;
}