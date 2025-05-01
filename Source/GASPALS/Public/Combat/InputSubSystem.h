// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/Queue.h"
#include "InputSubSystem.generated.h"


UENUM(BlueprintType)
enum class EInputActionType : uint8
{
	None UMETA(DisplayName = "None"),
	LightAttack UMETA(DisplayName = "LightAttack"),
	HeavyAttack UMETA(DisplayName = "HeavyAttack"),
	Execution UMETA(DisplayName = "Execution"),
	Block UMETA(DisplayName = "Block"),
	Dodge UMETA(DisplayName = "Dodge"),
	Dash UMETA(DisplayName = "Dash"),
	Interact UMETA(DisplayName = "Interact"),
	Jump UMETA(DisplayName = "Jump"),
	Ultimate UMETA(DisplayName = "Ultimate"),
	COUNT UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FBufferInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInputActionType InputActionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeStamp;

	FBufferInputAction(EInputActionType type, float time)
	{
		InputActionType = type;
		TimeStamp = time;
	}
	FBufferInputAction()
	{
		InputActionType = EInputActionType::None;
		TimeStamp = 0.0f;
	}
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class GASPALS_API UInputSubSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInputSubSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	//Input buffer for storing input actions
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input")
	TArray<FBufferInputAction> InputBuffer;

	//durations for when buffer remains valid
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input")
	float BufferDuration = 0.2f; 
	
public:
	//Add input action to buffer
	UFUNCTION(BlueprintCallable, Category = "Input")
	void AddInputActionToBuffer(EInputActionType InputActionType);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputAction, EInputActionType, InputActionType);
	
	UPROPERTY(BlueprintAssignable, Category = "Input")
	FOnInputAction OnInputActionAdded;
	
	//Check if input action is in buffer
	UFUNCTION(BlueprintCallable, Category = "Input")
	EInputActionType GetNextInputAction();

	UPROPERTY(BlueprintCallable, Category = "Input")
	FOnInputAction OnInputActionExecuted;

	//Check if input action is in buffer
	//Process input buffer
	UFUNCTION(BlueprintCallable, Category = "Input")
	EInputActionType ProcessInputBuffer();

	//Clear input buffer
	UFUNCTION(BlueprintCallable, Category = "Input")
	void ClearInputBuffer();

	UFUNCTION(BlueprintCallable, Category = "Input")
	bool ExecuteAction(EInputActionType InputActionType);
		
};
