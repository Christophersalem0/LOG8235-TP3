// Fill out your copyright notice in the Description page of Project Settings.

#include "AiAgentGroupManager.h"
#include "SoftDesignTraining.h"

AiAgentGroupManager* AiAgentGroupManager::m_Instance;

AiAgentGroupManager::AiAgentGroupManager()
{
}

AiAgentGroupManager* AiAgentGroupManager::GetInstance()
{
    if (!m_Instance)
    {
        m_Instance = new AiAgentGroupManager();
    }

    return m_Instance;
}

void AiAgentGroupManager::Destroy()
{
    delete m_Instance;
    m_Instance = nullptr;
}

void AiAgentGroupManager::Disband()
{
    for (auto agent : m_registeredAgents) {
        agent->IsInGroup = false;
    }
    m_registeredAgents.Empty();
}

void AiAgentGroupManager::RegisterAIAgent(ASDTBaseAIController* aiAgent)
{
    m_registeredAgents.Add(aiAgent);
}

void AiAgentGroupManager::UnregisterAIAgent(ASDTBaseAIController* aiAgent)
{
    aiAgent->IsInGroup = false;
    m_registeredAgents.Remove(aiAgent);
}

TargetLKPInfo AiAgentGroupManager::GetLKPFromGroup()
{
    return m_CurrentTargetLKPInfo;
}

void AiAgentGroupManager::SetGroupLKP(TargetLKPInfo targetLKPInfo) {
    m_CurrentTargetLKPInfo = targetLKPInfo;
    m_SeenThisTick = true;
}

void AiAgentGroupManager::InvalidLKP() {
    m_CurrentTargetLKPInfo.SetLKPState(TargetLKPInfo::ELKPState::LKPState_Invalid);
    if (!m_SeenThisTick) Disband();
}