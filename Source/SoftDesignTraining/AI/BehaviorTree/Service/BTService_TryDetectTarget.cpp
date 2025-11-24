// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_TryDetectTarget.h"

#include "SoftDesignTraining/SDTAIController.h"
#include "SoftDesignTraining/SDTUtils.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Kismet/GameplayStatics.h"

UBTService_TryDetectTarget::UBTService_TryDetectTarget()
{
    bCreateNodeInstance = true;
}

void UBTService_TryDetectTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner()))
    {
        bool canSeeTarget = aiController->m_PlayerInteractionBehavior == ASDTAIController::PlayerInteractionBehavior::PlayerInteractionBehavior_Chase || aiController->m_PlayerInteractionBehavior == ASDTAIController::PlayerInteractionBehavior::PlayerInteractionBehavior_Flee;
        OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(aiController->GetTargetSeenKeyID(), canSeeTarget);
    }
}

