// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystemInterface.h"
#include "MCharacter.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAttributeChangedDelegate, float, NewValue, float, OldValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNotifyEvent, bool, bStatus);

UCLASS()
class GASPALS_API AMCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
    UAbilitySystemComponent* AbilitySystemComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability|Tags")
    FGameplayTag DeathTag;

    // Attribute change handlers
    virtual void OnHealthChanged(const FOnAttributeChangeData& Data);
    virtual void OnMaxHealthChanged(const FOnAttributeChangeData& Data);
    virtual void OnEnergyChanged(const FOnAttributeChangeData& Data);
    virtual void OnMaxEnergyChanged(const FOnAttributeChangeData& Data);
    virtual void OnBaseDamageChanged(const FOnAttributeChangeData& Data);

    // Delegates for attribute changes
    UPROPERTY(BlueprintAssignable, Category = "Attributes")
    FAttributeChangedDelegate OnHealthChangedDelegate;

    UPROPERTY(BlueprintAssignable, Category = "Attributes")
    FAttributeChangedDelegate OnMaxHealthChangedDelegate;

    UPROPERTY(BlueprintAssignable, Category = "Attributes")
    FAttributeChangedDelegate OnEnergyChangedDelegate;

    UPROPERTY(BlueprintAssignable, Category = "Attributes")
    FAttributeChangedDelegate OnMaxEnergyChangedDelegate;

    UPROPERTY(BlueprintAssignable, Category = "Attributes")
    FAttributeChangedDelegate OnBaseDamageChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnNotifyEvent OnDeathNotifyEvent;

    void OnDeath();
};
