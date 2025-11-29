#pragma once
#include "TargetLKPInfo.h"
#include "SDTBaseAIController.h"
#include "CoreMinimal.h"

/**
 *
 */
class SOFTDESIGNTRAINING_API AiAgentGroupManager
{
public:
    static AiAgentGroupManager* GetInstance();
    static void Destroy();

    void RegisterAIAgent(ASDTBaseAIController* aiAgent);
    bool IsNearestToPlayer(ASDTBaseAIController* agentController);
    void CalculateNearestToPlayer(UWorld* world);
    void Disband();
    TargetLKPInfo GetLKPFromGroup();
    void SetGroupLKP(TargetLKPInfo targetLKPInfo);
    void InvalidLKP();
    void SetTargets(UWorld* world);
    bool IsGroupEmpty();

    bool m_SeenThisTick;
    TArray<ASDTBaseAIController*> m_registeredAgents;

private:

    //SINGLETON
    AiAgentGroupManager();
    int m_nbOfGroups = 8;
    TArray<FVector> m_circleLKP;
    static AiAgentGroupManager* m_Instance;
    TargetLKPInfo m_CurrentTargetLKPInfo;
    FTimerHandle m_RushTimer;
    ASDTBaseAIController* currentNearest;
};