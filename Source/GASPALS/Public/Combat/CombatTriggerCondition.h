#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"    
#include "CombatTriggerCondition.generated.h"


UCLASS(Blueprintable, Abstract)
class GASPALS_API ACombatTriggerCondition : public AActor
{
    GENERATED_BODY()

public:
    ACombatTriggerCondition();

    // Blueprint-native function to evaluate the trigger condition
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Combat")
    bool EvaluateTriggerCondition();

protected:
    // Actor reference that is instance editable and exposed on spawn
    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Combat", meta = (ExposeOnSpawn = "true"))
    AActor* TargetActor;
};