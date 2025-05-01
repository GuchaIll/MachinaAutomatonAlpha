#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatState.h"
#include "CombatInterface.generated.h"


UINTERFACE(Blueprintable)
class GASPALS_API UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class GASPALS_API ICombatInterface
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Combat")
    FCombatState GetCombatStateFromInputAction(EInputActionType InputActionType);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Combat")
    void ExecuteCombatAction(EInputActionType InputActionType);
};