// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SDTAIController.h"
#include "AgentsManager.generated.h"

UCLASS()
class SOFTDESIGNTRAINING_API AAgentsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAgentsManager();
	void RegisterAIAgent(ASDTAIController* aiAgent);
	void SetTickRate(ASDTAIController* aiAgent);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	float m_Budget = 2.f;

private:
	TArray<ASDTAIController*> m_Agents;
	int m_LastUpdatedIndex = 0;
};
