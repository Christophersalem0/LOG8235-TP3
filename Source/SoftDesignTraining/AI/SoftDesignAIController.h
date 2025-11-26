// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "SoftDesignAIController.generated.h"

/**
 * 
 */

UCLASS()
class SOFTDESIGNTRAINING_API ASoftDesignAIController : public AAIController
{
	GENERATED_BODY()
public:
	ASoftDesignAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	~ASoftDesignAIController();

	UBehaviorTreeComponent* GetBehaviorTreeComponent() const { return m_behaviorTreeComponent; }
	UBlackboardComponent* GetBlackBoardComponent() const { return m_blackboardComponent; }

	uint16                   GetTargetPosBBKeyID() const { return m_targetPosBBKeyID; }
	uint16                   GetTargetSeenKeyID() const { return m_isTargetSeenBBKeyID; }
	uint16                   GetNextPatrolDestinationKeyID() const { return m_nextPatrolDestinationBBKeyID; }
	uint16                   GetCurrentPatrolDestinationKeyID() const { return m_currentPatrolDestinationBBKeyID; }
	uint16                   GetIsInGroupKeyID() const { return m_isInGroupKeyID; }


	void                    StartBehaviorTree(AAIController* aiBaseCharacter);
	void                    StopBehaviorTree(AAIController* aiBaseCharacter);

protected:
	virtual void OnPossess(APawn* pawn) override;


	UPROPERTY(transient)
	UBehaviorTreeComponent* m_behaviorTreeComponent;

	UPROPERTY(transient)
	UBlackboardComponent* m_blackboardComponent;

private:


	uint16  m_targetPosBBKeyID;
	uint16  m_isInGroupKeyID;
	uint16  m_isTargetSeenBBKeyID;
	uint16  m_nextPatrolDestinationBBKeyID;
	uint16  m_currentPatrolDestinationBBKeyID;
};
