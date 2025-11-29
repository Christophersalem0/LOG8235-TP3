// Fill out your copyright notice in the Description page of Project Settings.

#include "SDTBaseAIController.h"
#include "SoftDesignTraining.h"

ASDTBaseAIController::ASDTBaseAIController(const FObjectInitializer& ObjectInitializer)
    :ASoftDesignAIController(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;
    m_ReachedTarget = true;
    IsInGroup = false;
    CanSeePlayer = false;
}

void ASDTBaseAIController::Tick(float deltaTime)
{
    Super::Tick(deltaTime);

    //UpdatePlayerInteraction(deltaTime);

    /*if (m_ReachedTarget)
    {
        GoToBestTarget(deltaTime);
    }
    else
    {
        ShowNavigationPath();
    }*/
}

void ASDTBaseAIController::leaveGroup() {
    IsInGroup = false;
    if (m_blackboardComponent)
        m_blackboardComponent->SetValue<UBlackboardKeyType_Bool>(GetIsInGroupKeyID(), IsInGroup);
};


