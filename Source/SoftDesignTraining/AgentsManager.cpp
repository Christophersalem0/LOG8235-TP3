// Fill out your copyright notice in the Description page of Project Settings.


#include "AgentsManager.h"
#include "AiAgentGroupManager.h"
#include "SDTUtils.h"

// Sets default values
AAgentsManager::AAgentsManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void AAgentsManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAgentsManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	AiAgentGroupManager::GetInstance()->Destroy();
}


// Called every frame
void AAgentsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AiAgentGroupManager* AgentGroupManager = AiAgentGroupManager::GetInstance();
	AgentGroupManager->m_SeenThisTick = false;

	auto currentTime = FPlatformTime::Seconds();
	int stopIdx = m_LastUpdatedIndex;
	
	if (SDTUtils::IsPlayerPoweredUp(GetWorld())) {
		AgentGroupManager->InvalidLKP();
		AgentGroupManager->Disband();
	}

	 do {
		ASDTAIController* agent = m_Agents[m_LastUpdatedIndex];
		if (!agent->IsInGroup || !AgentGroupManager->m_SeenThisTick) {
			agent->DetectPlayer(DeltaTime);
		}
		m_LastUpdatedIndex = (m_LastUpdatedIndex + 1) % m_Agents.Num();
	 } while ((FPlatformTime::Seconds() - currentTime) * 1000 < m_Budget && stopIdx != m_LastUpdatedIndex);

	if (!AgentGroupManager->m_SeenThisTick && AgentGroupManager->GetLKPFromGroup().GetLKPState() == TargetLKPInfo::ELKPState::LKPState_Invalid && !AgentGroupManager->IsGroupEmpty()) {
		AgentGroupManager->Disband();
	}

	AgentGroupManager->SetTargets(GetWorld());
}

void AAgentsManager::RegisterAIAgent(ASDTAIController* aiAgent)
{
	m_Agents.Add(aiAgent);
}

