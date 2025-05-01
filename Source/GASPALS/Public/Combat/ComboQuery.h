#pragma once

#include "CoreMinimal.h"
#include "CombatState.h"
#include "ComboQuery.generated.h"

//trie representation of combo sequences for querying
//highest child priority node is evaluated first
//entrance and exit conditions are evaluated

UCLASS(Blueprintable)
class GASPALS_API UComboQueryNode : public UObject
{
    GENERATED_BODY()

    public:
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
        FCombatState CombatState;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
        TMap<EInputActionType, UComboQueryNode*> Children;
        
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
        bool EndCombo;

        
};


UCLASS(Blueprintable, Abstract)
class GASPALS_API UComboQuery : public UObject
{
    GENERATED_BODY()

    public:

        UComboQuery();

        UFUNCTION(BlueprintCallable, Category = "Combat")
        FCombatState EvaluateComboQuery(UComboQueryNode *ComboQueryNode, EInputActionType NextInput, bool ResetCombo = true);

        UFUNCTION(BlueprintCallable, Category = "Combat")
        void AddComboQueryNode(const TArray<EInputActionType>& ComboSequence, const FCombatState& CombatState);

        UFUNCTION(BlueprintCallable, Category = "Combo")
        TArray<UComboQueryNode *> QueryNextNode();

        UFUNCTION(BlueprintCallable, Category = "Combo")
        UComboQueryNode *GetRootNode();

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
        UComboQueryNode *RootNode;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
        UComboQueryNode *CurrentComboNode;

    };