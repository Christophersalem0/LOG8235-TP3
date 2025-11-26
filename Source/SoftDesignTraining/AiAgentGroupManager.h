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
    TargetLKPInfo GetLKPFromGroup(const FString& targetLabel, bool& targetFound);

private:

    //SINGLETON
    AiAgentGroupManager();
    static AiAgentGroupManager* m_Instance;

    TArray<ASDTBaseAIController*> m_registeredAgents;

};