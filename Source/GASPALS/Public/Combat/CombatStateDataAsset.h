#pragma once

#include "CoreMinimal.h"
#include "CombatState.h"
#include "Engine/DataTable.h"
#include "CombatStateDataAsset.generated.h"

UCLASS(BlueprintType)
class GASPALS_API UCombatStateDataAsset : public UDataAsset
{
    GENERATED_BODY()

    public:
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
        TArray<FCombatState> CombatStates;
};