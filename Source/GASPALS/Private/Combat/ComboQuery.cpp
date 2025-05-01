#include "Combat/ComboQuery.h"
#include "Combat/InputSubSystem.h"


UComboQuery::UComboQuery()
{
    RootNode = NewObject<UComboQueryNode>();

    if(!RootNode)
    {
        UE_LOG(LogTemp, Log, TEXT("Failed to create RootNode"));
        return;
    }

    CurrentComboNode = RootNode;

    for(int i = 0; i < (int)EInputActionType::COUNT; i++)
    {
        RootNode->Children.Add((EInputActionType)i, nullptr);
    }

    RootNode->CombatState = FCombatState();
}

FCombatState UComboQuery::EvaluateComboQuery(UComboQueryNode *ComboQueryNode, EInputActionType NextInput, bool ResetCombo)
{
    UComboQueryNode *CurrentNode = CurrentComboNode;

    if(CurrentNode->Children[NextInput] != nullptr)
    {
        CurrentNode = CurrentNode->Children[NextInput];

        if(CurrentNode->EndCombo)
        {
            if(ResetCombo)
            {
                UE_LOG(LogTemp, Log, TEXT("Node CombatState: %s"), *CurrentNode->CombatState.StateName.ToString());
                CurrentComboNode = RootNode;
            }
            return CurrentNode->CombatState;
        }
        else
        {
            CurrentComboNode = CurrentNode;
            return CurrentNode->CombatState;
        }
       
    }

    UE_LOG(LogTemp, Log, TEXT("Invalid Combo:"));
    return FCombatState();

}


void UComboQuery::AddComboQueryNode(const TArray<EInputActionType> &ComboSequence, const FCombatState &CombatState)
{
    if(ComboSequence.Num() == 0)
    {
        UE_LOG(LogTemp, Log, TEXT("AddComboQueryNode: Empty ComboSequence"));
        return;
    }
    UComboQueryNode *CurrentNode = RootNode;

    for(int i = 0; i < ComboSequence.Num(); i++)
    {
        EInputActionType InputAction = ComboSequence[i];

        if(CurrentNode->Children[InputAction] == nullptr)
        {
            CurrentNode->Children[InputAction] = NewObject<UComboQueryNode>();
            CurrentNode->EndCombo = false;
        }
        CurrentNode = CurrentNode->Children[InputAction];
    }
    CurrentNode->CombatState = CombatState;
    CurrentNode->EndCombo = true;
}

TArray<UComboQueryNode *> UComboQuery::QueryNextNode()
{
    TArray<UComboQueryNode *> NextNodes;
    UComboQueryNode *CurrentNode = CurrentComboNode;
    for(int i = 0; i < (int)EInputActionType::COUNT; i++)
    {
        if(CurrentNode->Children[(EInputActionType)i] != nullptr)
        {
            NextNodes.Add(CurrentNode->Children[(EInputActionType)i]);
        }
    }
    return NextNodes;
}

UComboQueryNode *UComboQuery::GetRootNode()
{
    return RootNode;
}
