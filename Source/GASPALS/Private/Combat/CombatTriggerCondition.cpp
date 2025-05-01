#include "Combat/CombatTriggerCondition.h"


ACombatTriggerCondition::ACombatTriggerCondition()
{
    // Enable ticking if needed
    PrimaryActorTick.bCanEverTick = true;

    // Initialize any other properties here
}

bool ACombatTriggerCondition::EvaluateTriggerCondition_Implementation()
{
    return false;
}