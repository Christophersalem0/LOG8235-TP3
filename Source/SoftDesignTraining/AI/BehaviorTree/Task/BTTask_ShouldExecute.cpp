// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ShouldExecute.h"
#include "SoftDesignTraining/SDTAIController.h"



EBTNodeResult::Type UBTTask_ShouldExecute::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {
        if (OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Bool>(aiController->GetShouldExecute()))
        {
            aiController->SetShouldExecute(false);
            return EBTNodeResult::Succeeded;
        }
    }

    return EBTNodeResult::Failed;
}
