#include "Combat/Attributes/MAttributes.h"
#include "Net/UnrealNetwork.h"

UMAttributes::UMAttributes()
{
    // Initialize default values for attributes
    Health = 100.0f;
    MaxHealth = 100.0f;

    Energy = 0.0f;
    MaxEnergy = 100.0f;

    BaseDamage = 10.0f;
}

void UMAttributes::OnRep_Health(const FGameplayAttributeData& OldValue)
{
    float OldHealth = OldValue.GetCurrentValue();
    float NewHealth = Health.GetCurrentValue();
    float MaxHealthValue = MaxHealth.GetCurrentValue();

    OnHealthChanged.Broadcast(NewHealth, OldHealth, MaxHealthValue);

    UE_LOG(LogTemp, Log, TEXT("Health changed: OldValue = %f, NewValue = %f, MaxValue = %f"), OldHealth, NewHealth, MaxHealthValue);

    GAMEPLAYATTRIBUTE_REPNOTIFY(UMAttributes, Health, OldValue);
}

void UMAttributes::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMAttributes, MaxHealth, OldValue);
}

void UMAttributes::OnRep_Energy(const FGameplayAttributeData& OldValue)
{
    
    float OldEnergy = OldValue.GetCurrentValue();
    float NewEnergy = Energy.GetCurrentValue();
    float MaxEnergyValue = MaxEnergy.GetCurrentValue();

    // Broadcast the change
    OnEnergyChanged.Broadcast(NewEnergy, OldEnergy, MaxEnergyValue);

    GAMEPLAYATTRIBUTE_REPNOTIFY(UMAttributes, Energy, OldValue);
}

void UMAttributes::OnRep_MaxEnergy(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMAttributes, MaxEnergy, OldValue);
}

void UMAttributes::OnRep_BaseDamage(const FGameplayAttributeData& OldValue)
{
    float OldBaseDamage = OldValue.GetCurrentValue();
    float NewBaseDamage = BaseDamage.GetCurrentValue();

    // Broadcast the change (no max value for BaseDamage in this case)
    OnBaseDamageChanged.Broadcast(NewBaseDamage, OldBaseDamage, 3500.0f);

    GAMEPLAYATTRIBUTE_REPNOTIFY(UMAttributes, BaseDamage, OldValue);
}

void UMAttributes::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UMAttributes, Health);
    DOREPLIFETIME(UMAttributes, MaxHealth);
    DOREPLIFETIME(UMAttributes, Energy);
    DOREPLIFETIME(UMAttributes, MaxEnergy);
    DOREPLIFETIME(UMAttributes, BaseDamage);
    
}