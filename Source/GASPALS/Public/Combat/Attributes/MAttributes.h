#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MAttributes.generated.h"

// Macro to simplify attribute replication
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChanged, float, NewValue, float, OldValue, float, MaxValue);

UCLASS()
class GASPALS_API UMAttributes : public UAttributeSet
{
    GENERATED_BODY()

public:
    UMAttributes();

    // Health Attribute
    UPROPERTY(BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_Health)
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UMAttributes, Health)

     // Max Health Attribute
     UPROPERTY(BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_MaxHealth)
     FGameplayAttributeData MaxHealth;
     ATTRIBUTE_ACCESSORS(UMAttributes, MaxHealth)

    UPROPERTY(BlueprintAssignable, Category = "Attributes")
    FOnAttributeChanged OnHealthChanged;
    // Energy Attribute

    UPROPERTY(BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_Energy)
    FGameplayAttributeData Energy;
    ATTRIBUTE_ACCESSORS(UMAttributes, Energy)

    UPROPERTY(BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_MaxEnergy)
    FGameplayAttributeData MaxEnergy;
    ATTRIBUTE_ACCESSORS(UMAttributes, MaxEnergy)

    UPROPERTY(BlueprintAssignable, Category = "Attributes")
    FOnAttributeChanged OnEnergyChanged;

    // Base Damage Attribute
    UPROPERTY(BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_BaseDamage)
    FGameplayAttributeData BaseDamage;
    ATTRIBUTE_ACCESSORS(UMAttributes, BaseDamage)

    UPROPERTY(BlueprintAssignable, Category = "Attributes")
    FOnAttributeChanged OnBaseDamageChanged;


    // Replication callbacks
    UFUNCTION()
    virtual void OnRep_Health(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    virtual void OnRep_Energy(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    virtual void OnRep_MaxEnergy(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    virtual void OnRep_BaseDamage(const FGameplayAttributeData& OldValue);

    
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};