// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SDTBaseAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "SDTAIController.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EAIBrainMode : uint8
{
    IfElse          UMETA(DisplayName = "IfElse_Logic"),
    BehaviorTree 	UMETA(DisplayName = "BT_Logic")
};

UCLASS(ClassGroup = AI, config = Game)
class SOFTDESIGNTRAINING_API ASDTAIController : public ASDTBaseAIController
{
	GENERATED_BODY()

public:
    ASDTAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
    virtual void Tick(float deltaTime) override;
    virtual void BeginPlay() override;

    UBehaviorTree* GetBehaviorTree() const { return m_aiBehaviorTree; }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
    float m_DetectionCapsuleHalfLength = 500.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
    float m_DetectionCapsuleRadius = 250.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
    float m_DetectionCapsuleForwardStartingOffset = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
    UCurveFloat* JumpCurve;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
    float JumpApexHeight = 300.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
    float JumpSpeed = 1.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI)
    bool AtJumpSegment = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI)
    bool InAir = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI)
    bool Landing = false;   

    enum PlayerInteractionBehavior
    {
        PlayerInteractionBehavior_Collect,
        PlayerInteractionBehavior_Chase,
        PlayerInteractionBehavior_Flee
    };

protected:

    UPROPERTY(EditAnywhere, category = Behavior)
    UBehaviorTree* m_aiBehaviorTree;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decision_Exercises")
    EAIBrainMode m_currentBrainLogic;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
    bool m_DrawDebug;

    void GetHightestPriorityDetectionHit(const TArray<FHitResult>& hits, FHitResult& outDetectionHit);
    void UpdatePlayerInteractionBehavior(const FHitResult& detectionHit, float deltaTime);
    void UpdateBTLogic(float deltaTime);
    PlayerInteractionBehavior GetCurrentPlayerInteractionBehavior(const FHitResult& hit);
    bool HasLoSOnHit(const FHitResult& hit);
    void OnPlayerInteractionNoLosDone();

public:
    virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
    void RotateTowards(const FVector& targetLocation);
    void SetActorLocation(const FVector& targetLocation);
    void AIStateInterrupted();
    void OnMoveToTarget();
    void MoveToRandomCollectible();
    FVector3d MoveToBestFleeLocation(bool shouldMove = true);
    void MoveToPlayer();
    void MoveToLKP();
    void DetectPlayer(float deltaTime);
    void GroupSphere();
    void SetShouldExecute(bool valueToSet);
    PlayerInteractionBehavior m_PlayerInteractionBehavior;

private:
    virtual void GoToBestTarget(float deltaTime) override;
    virtual void ShowNavigationPath() override;
    void PlayerInteractionLoSUpdate();
    virtual void UpdatePlayerInteraction(float deltaTime) override;


protected:
    FVector m_JumpTarget;
    FRotator m_ObstacleAvoidanceRotation;
    FTimerHandle m_PlayerInteractionNoLosTimer;
};
