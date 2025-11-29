// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SoftDesignTraining/AI/SoftDesignAIController.h"
#include "TargetLKPInfo.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "SDTBaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class SOFTDESIGNTRAINING_API ASDTBaseAIController : public ASoftDesignAIController
{
	GENERATED_BODY()

public:

    ASDTBaseAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
    virtual void Tick(float deltaTime) override;
    virtual TargetLKPInfo GetCurrentTargetLKPInfo() { return m_CurrentLKPInfo; };
    void leaveGroup();
    bool m_ReachedTarget;
    bool IsInGroup;
    bool CanSeePlayer;
    FVector target;
	
protected:
    virtual void RotationUpdate(float deltaTime) {};
    virtual void ImpulseToDirection(float deltaTime) {};
    TargetLKPInfo m_CurrentLKPInfo;

private:
    virtual void GoToBestTarget(float deltaTime) {};
    virtual void UpdatePlayerInteraction(float deltaTime) {};
    virtual void ShowNavigationPath() {};
};
