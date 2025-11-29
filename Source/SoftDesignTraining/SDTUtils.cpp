// Fill out your copyright notice in the Description page of Project Settings.

#include "SDTUtils.h"
#include "SoftDesignTraining.h"
#include "SoftDesignTrainingMainCharacter.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include <NavigationSystem.h>

/*static*/ bool SDTUtils::Raycast(UWorld* uWorld, FVector sourcePoint, FVector targetPoint)
{
    FHitResult hitData;
    FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true);
    
    // Fake cost for the exercise
    //Sleep(1);
    // End fake cost

    return uWorld->LineTraceSingleByChannel(hitData, sourcePoint, targetPoint, ECC_Pawn, TraceParams);
}

bool SDTUtils::IsPlayerPoweredUp(UWorld * uWorld)
{
    ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(uWorld, 0);
    if (!playerCharacter)
        return false;

    ASoftDesignTrainingMainCharacter* castedPlayerCharacter = Cast<ASoftDesignTrainingMainCharacter>(playerCharacter);
    if (!castedPlayerCharacter)
        return false;

    return castedPlayerCharacter->IsPoweredUp();
}

bool SDTUtils::RaycastNavMesh(UWorld* uWorld, FVector sourcePoint, FVector targetPoint)
{
    FVector hitLocation;
    UNavigationSystemV1::NavigationRaycast(uWorld, sourcePoint, targetPoint, hitLocation);

    return (hitLocation - targetPoint).IsNearlyZero();
}

bool SDTUtils::GetNearestNavMeshPoint(UWorld* uWorld, ASDTAIController* Controller, FVector& Location)
{
    UNavigationSystemV1* NavSys = UNavigationSystemV1::GetNavigationSystem(uWorld);
    const FNavAgentProperties& AgentProps = Controller->GetNavAgentPropertiesRef();
    if (NavSys != nullptr)
    {
        FNavLocation ProjectedLocation;
        NavSys->ProjectPointToNavigation(Controller->target, ProjectedLocation, FVector(500.0f, 500.0f, 300.0f), &AgentProps);
        Location = ProjectedLocation.Location;
        return true;
    }
   
    return false;
}