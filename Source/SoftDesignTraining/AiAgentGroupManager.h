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
    void UnregisterAIAgent(ASDTBaseAIController* aiAgent);
    void Disband();
    TargetLKPInfo GetLKPFromGroup();
    void SetGroupLKP(TargetLKPInfo targetLKPInfo);
    void InvalidLKP();

    bool m_SeenThisTick;

private:

    //SINGLETON
    AiAgentGroupManager();
    static AiAgentGroupManager* m_Instance;
    TargetLKPInfo m_CurrentTargetLKPInfo;
    TArray<ASDTBaseAIController*> m_registeredAgents;

};