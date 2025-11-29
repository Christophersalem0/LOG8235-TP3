// Fill out your copyright notice in the Description page of Project Settings.

#include "AiAgentGroupManager.h"
#include "SoftDesignTraining.h"

AiAgentGroupManager* AiAgentGroupManager::m_Instance;

AiAgentGroupManager::AiAgentGroupManager()
{
    for (int i = 0; i < m_nbOfGroups; i++) {
        m_circleLKP.Add(FVector(FMath::Cos(i * 360 / m_nbOfGroups * PI / 180) * 500, FMath::Sin(i * 360 / m_nbOfGroups * PI / 180) * 500, 0));
        FVector MyVector = m_circleLKP[i];
        UE_LOG(LogTemp, Warning, TEXT("My Vector: X=%.2f, Y=%.2f, Z=%.2f"), MyVector.X, MyVector.Y, MyVector.Z);
    }
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
    UE_LOG(LogTemp, Warning, TEXT("DISBAND"));
    m_CurrentTargetLKPInfo.SetLKPState(TargetLKPInfo::ELKPState::LKPState_Invalid);
    for (auto agent : m_registeredAgents) {
        agent->leaveGroup();
        agent->m_ReachedTarget = true;
    }
    m_registeredAgents.Empty();
}

void AiAgentGroupManager::RegisterAIAgent(ASDTBaseAIController* aiAgent)
{
    m_registeredAgents.Add(aiAgent);
}

TargetLKPInfo AiAgentGroupManager::GetLKPFromGroup()
{
    return m_CurrentTargetLKPInfo;
}

void AiAgentGroupManager::SetGroupLKP(TargetLKPInfo targetLKPInfo) {
    m_CurrentTargetLKPInfo = targetLKPInfo;
}

void AiAgentGroupManager::InvalidLKP() {
    m_CurrentTargetLKPInfo.SetLKPState(TargetLKPInfo::ELKPState::LKPState_Invalid);
}

void AiAgentGroupManager::SetTargets() {
    for (int i = 0; i < m_registeredAgents.Num(); i++) {
        int index = i % m_nbOfGroups;
        FVector target = m_CurrentTargetLKPInfo.GetLKPPos() + m_circleLKP[index]; 
        m_registeredAgents[i]->target = target;
    }
}

bool AiAgentGroupManager::IsGroupEmpty() {
    return m_registeredAgents.Num() == 0;
}

bool AiAgentGroupManager::IsNearestToPlayer(ASDTBaseAIController* agentController, UWorld* world) {
    ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(world, 0);
    if (!playerCharacter)
        return false;

    float DistanceToPlayer = (agentController->GetPawn()->GetActorLocation() - playerCharacter->GetActorLocation()).SizeSquared();
    DrawDebugString(world, FVector(0.f, 0.f, 10.f), FString::SanitizeFloat(DistanceToPlayer), agentController->GetPawn(), FColor::Red, 5.f, false);

    for (auto& agent : m_registeredAgents) {
        if ((agent->GetPawn()->GetActorLocation() - playerCharacter->GetActorLocation()).SizeSquared() < DistanceToPlayer + 100) {
            if (agent != agentController)
                return false;
        }

    }

    return true;
}