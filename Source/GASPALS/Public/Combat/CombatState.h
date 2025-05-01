#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "CombatTriggerCondition.h"

#include "CombatState.generated.h"

UENUM(BlueprintType)
enum class EDamageExecutionType : uint8
{
    Immediate UMETA(DisplayName = "Immediate"),
    Delayed UMETA(DisplayName = "Delayed")
};


USTRUCT(BlueprintType)
struct FCombatState
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    FName StateName;

    //Animation montage corresponding to current combat state
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    UAnimMontage* ActiveMontage;

    //Trigger conditions for the current combat state
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    TArray<TSubclassOf<ACombatTriggerCondition>> TriggerConditions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    TArray<TSubclassOf<UGameplayEffect>> GameplayEffects;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    EDamageExecutionType DamageExecutionType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float BaseDamageAmount;


    FCombatState(){
        StateName = FName("None");
        ActiveMontage = nullptr;
        DamageExecutionType = EDamageExecutionType::Immediate;
        BaseDamageAmount = 0.0f;
    }

};