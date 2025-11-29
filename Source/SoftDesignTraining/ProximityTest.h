// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "ProximityTest.generated.h"

/**
 * 
 */
UCLASS()
class SOFTDESIGNTRAINING_API UProximityTest : public UEnvQueryTest
{
	GENERATED_BODY()
public:
	UProximityTest(const FObjectInitializer& ObjectInitializer);

    // The core function where the testing logic happens
    virtual void RunTest(FEnvQueryInstance& Instance) const override;

    // Define the range we care about for proximity scoring
    UPROPERTY(EditDefaultsOnly, Category = Filter)
    float ProximityMaxDistance;
};

