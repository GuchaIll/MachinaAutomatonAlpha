// Fill out your copyright notice in the Description page of Project Settings.


#include "MCharacter.h"
#include "AbilitySystemComponent.h"
#include "Combat/Attributes/MAttributes.h"

// Sets default values
AMCharacter::AMCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	if(AbilitySystemComponent)
	{
    	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UMAttributes::GetHealthAttribute()).AddUObject(this, &AMCharacter::OnHealthChanged);
    	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UMAttributes::GetMaxHealthAttribute()).AddUObject(this, &AMCharacter::OnMaxHealthChanged);
    	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UMAttributes::GetEnergyAttribute()).AddUObject(this, &AMCharacter::OnEnergyChanged);
    	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UMAttributes::GetMaxEnergyAttribute()).AddUObject(this, &AMCharacter::OnMaxEnergyChanged);
    	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UMAttributes::GetBaseDamageAttribute()).AddUObject(this, &AMCharacter::OnBaseDamageChanged);
	
}}	

// Called when the game starts or when spawned
void AMCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMCharacter::OnHealthChanged(const FOnAttributeChangeData& Data)
{
    float NewValue = Data.NewValue;
    float OldValue = Data.OldValue;

    OnHealthChangedDelegate.Broadcast(NewValue, OldValue);

    if (AbilitySystemComponent)
    {
        if (NewValue <= 0.0f && !AbilitySystemComponent->HasMatchingGameplayTag(DeathTag))
        {
            AbilitySystemComponent->AddLooseGameplayTag(DeathTag);
            OnDeath();
        }
    }
}

void AMCharacter::OnMaxHealthChanged(const FOnAttributeChangeData& Data)
{
    float NewValue = Data.NewValue;
    float OldValue = Data.OldValue;

    OnMaxHealthChangedDelegate.Broadcast(NewValue, OldValue);
}

void AMCharacter::OnEnergyChanged(const FOnAttributeChangeData& Data)
{
    float NewValue = Data.NewValue;
    float OldValue = Data.OldValue;

    OnEnergyChangedDelegate.Broadcast(NewValue, OldValue);
}

void AMCharacter::OnMaxEnergyChanged(const FOnAttributeChangeData& Data)
{
    float NewValue = Data.NewValue;
    float OldValue = Data.OldValue;

    OnMaxEnergyChangedDelegate.Broadcast(NewValue, OldValue);
}

void AMCharacter::OnBaseDamageChanged(const FOnAttributeChangeData& Data)
{
    float NewValue = Data.NewValue;
    float OldValue = Data.OldValue;

    OnBaseDamageChangedDelegate.Broadcast(NewValue, OldValue);
}

void AMCharacter::OnDeath()
{
	OnDeathNotifyEvent.Broadcast(true); // Notify listeners that the character has died
    UE_LOG(LogTemp, Log, TEXT("Character has died."));
}