// Fill out your copyright notice in the Description page of Project Settings.


#include "ProximityTest.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_VectorBase.h"
#include "AiAgentGroupManager.h"

UProximityTest::UProximityTest(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    // Ensure the Test Result is expected to be a score value (usually 0 to 1)
    Cost = EEnvTestCost::Low;
    ValidItemType = UEnvQueryItemType_VectorBase::StaticClass();
    // Default max distance for sanity
    ProximityMaxDistance = 1000.f;
}


void UProximityTest::RunTest(FEnvQueryInstance& Instance) const {


    TArray<FEnvQueryItem>& Items = Instance.Items;
    if (Items.Num() == 0)
    {
        return;
    }

    AiAgentGroupManager* Group = AiAgentGroupManager::GetInstance();
    if (Group->m_registeredAgents.Num() <= 1)
    {
        // If no allies exist, all points are equally good, so we score them neutrally (1.0)
        for (FEnvQueryItem& Item : Items)
        {
            Item.Score = 1.0f;
        }
        return;
    }

    // 3. Score each potential location based on distance to the nearest ally
    for (int i = 0; i < Items.Num(); i++)
    {
        FEnvQueryItem& item = Items[i];
        const FVector ItemLocation = GetItemLocation(Instance, i);
        float MinDistanceSq = MAX_FLT;

        // Find the distance to the closest ally
        for (const auto& Ally : Group->m_registeredAgents)
        {
            if (Ally->GetPawn()) {
                const float DistSq = FVector::DistSquared(ItemLocation, Ally->GetPawn()->GetActorLocation());
                if (DistSq < MinDistanceSq)
                {
                    MinDistanceSq = DistSq;
                }
            }
        }

        const float MinDistance = FMath::Sqrt(MinDistanceSq);

        // Use a scoring mechanism:
        // We want a high score for locations with LOW proximity to an ally.
        // FMath::Clamp ensures the value stays between 0 and 1.
        // We use (ProximityMaxDistance - MinDistance) to inverse the score for 'closer' distances.
        item.Score = MinDistance;
    }
}