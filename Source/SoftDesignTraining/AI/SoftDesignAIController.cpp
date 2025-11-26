// Fill out your copyright notice in the Description page of Project Settings.


#include "SoftDesignAIController.h"
#include "SoftDesignTraining/SDTAIController.h"


ASoftDesignAIController::ASoftDesignAIController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer),
    m_targetPosBBKeyID(0),
    m_isTargetSeenBBKeyID(0)
{
    m_behaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
    m_blackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

ASoftDesignAIController::~ASoftDesignAIController()
{

}

void ASoftDesignAIController::StartBehaviorTree(AAIController* aiBaseCharacter)
{
    if (ASDTAIController* aiCharacter = Cast<ASDTAIController>(aiBaseCharacter))
    {
        if (aiCharacter->GetBehaviorTree())
        {
            m_behaviorTreeComponent->StartTree(*aiCharacter->GetBehaviorTree());
        }
    }
}

void ASoftDesignAIController::StopBehaviorTree(AAIController* aiBaseCharacter)
{
    if (ASDTAIController* aiCharacter = Cast<ASDTAIController>(aiBaseCharacter))
    {
        if (aiCharacter->GetBehaviorTree())
        {
            m_behaviorTreeComponent->StopTree();
        }
    }
}

void ASoftDesignAIController::OnPossess(APawn* pawn)
{
    Super::OnPossess(pawn);

    if (ASDTAIController* aiBaseCharacter = Cast<ASDTAIController>(pawn->GetController()))
    {
        if (aiBaseCharacter->GetBehaviorTree())
        {
            m_blackboardComponent->InitializeBlackboard(*aiBaseCharacter->GetBehaviorTree()->BlackboardAsset);

            m_targetPosBBKeyID = m_blackboardComponent->GetKeyID("TargetPos");
            m_isTargetSeenBBKeyID = m_blackboardComponent->GetKeyID("TargetIsSeen");
            m_nextPatrolDestinationBBKeyID = m_blackboardComponent->GetKeyID("NextPatrolDest");
            m_currentPatrolDestinationBBKeyID = m_blackboardComponent->GetKeyID("CurrentPatrolDest");

            //Set this agent in the BT
            m_blackboardComponent->SetValue<UBlackboardKeyType_Object>(m_blackboardComponent->GetKeyID("SelfActor"), pawn);
        }
    }
}


