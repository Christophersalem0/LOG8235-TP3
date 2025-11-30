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
    //UE_LOG(LogTemp, Warning, TEXT("DISBAND"));
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

void AiAgentGroupManager::SetTargets(UWorld* world) {
    if (m_nbOfGroups != m_registeredAgents.Num() && m_registeredAgents.Num() < 9) {
        m_nbOfGroups = FMath::Min(8, m_registeredAgents.Num());
        m_circleLKP.Empty();
        for (int i = 0; i < m_nbOfGroups; i++) {
            m_circleLKP.Add(FVector(FMath::Cos(i * 360 / m_nbOfGroups * PI / 180), FMath::Sin(i * 360 / m_nbOfGroups * PI / 180), 0));
        }
    }
    ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(world, 0);
    if (!playerCharacter)
        return;
    for (int i = 0; i < m_registeredAgents.Num(); i++) {
        int index = i % m_nbOfGroups;
        FVector target = m_CurrentTargetLKPInfo.GetLKPPos() + m_circleLKP[index] * (m_registeredAgents[i]->GetPawn()->GetActorLocation() - playerCharacter->GetActorLocation()).Size() * FMath::Min(.9, .5 * (float(i) / float(m_nbOfGroups) + 1));
        //DrawDebugSphere(world, target + FVector(0.f, 0.f, 100.f), 15.0f, 32, FColor::Blue);
        m_registeredAgents[i]->target = target;
    }
}

bool AiAgentGroupManager::IsGroupEmpty() {
    return m_registeredAgents.Num() == 0;
}

void AiAgentGroupManager::CalculateNearestToPlayer(UWorld* world) {
    if (world->GetTimerManager().IsTimerActive(m_RushTimer) && currentNearest != nullptr || m_registeredAgents.IsEmpty())
        return;
    ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(world, 0);
    if (!playerCharacter)
        return;

    float LowestDistanceToPlayer = MAX_FLT;
    //DrawDebugString(world, FVector(0.f, 0.f, 10.f), FString::SanitizeFloat(DistanceToPlayer), agentController->GetPawn(), FColor::Red, 5.f, false);

    for (auto& agent : m_registeredAgents) {
        float DistanceToPlayer = (agent->GetPawn()->GetActorLocation() - playerCharacter->GetActorLocation()).SizeSquared();
        if (DistanceToPlayer < LowestDistanceToPlayer) {
            currentNearest = agent;
            LowestDistanceToPlayer = DistanceToPlayer;
        }
    }
    world->GetTimerManager().SetTimer(
        m_RushTimer,
        [this, world]() { CalculateNearestToPlayer(world); },
        1.f,
        false
    );
}

bool AiAgentGroupManager::IsNearestToPlayer(ASDTBaseAIController* agentController) {
    return agentController == currentNearest;
}