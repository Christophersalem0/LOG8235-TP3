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
    bool IsNearestToPlayer(ASDTBaseAIController* agentController, UWorld* world);
    void Disband();
    TargetLKPInfo GetLKPFromGroup();
    void SetGroupLKP(TargetLKPInfo targetLKPInfo);
    void InvalidLKP();
    void SetTargets();
    bool IsGroupEmpty();

    bool m_SeenThisTick;
    TArray<ASDTBaseAIController*> m_registeredAgents;

private:

    //SINGLETON
    AiAgentGroupManager();
    const int m_nbOfGroups = 8;
    TArray<FVector> m_circleLKP;
    static AiAgentGroupManager* m_Instance;
    TargetLKPInfo m_CurrentTargetLKPInfo;

};