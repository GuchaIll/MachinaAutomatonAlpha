// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/InputSubSystem.h"


// Sets default values for this component's properties
UInputSubSystem::UInputSubSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UInputSubSystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInputSubSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//Input buffer, queue for processing input actions, new input actions are added to the end of the queue
//Input actions at the front of the queue are processed first
void UInputSubSystem::AddInputActionToBuffer(EInputActionType InputActionType)
{
	FBufferInputAction newInputAction = FBufferInputAction(InputActionType, GetWorld()->GetTimeSeconds());
	InputBuffer.Add(newInputAction);

	OnInputActionAdded.Broadcast(InputActionType);
}

EInputActionType UInputSubSystem::GetNextInputAction()
{
    if(InputBuffer.IsEmpty())
	{
		return EInputActionType::None;
	}
	else
	{
		return InputBuffer[0].InputActionType;
	}
}

//Process Input buffer by dequeuing all expired input actions
//and try executing the first valid input action
EInputActionType UInputSubSystem::ProcessInputBuffer()
{
	float currentTime = GetWorld()->GetTimeSeconds();
	
    EInputActionType inputActionType = EInputActionType::None;
	while(InputBuffer.Num() > 0)
	{
		if (currentTime - InputBuffer[0].TimeStamp > BufferDuration)
		{
			InputBuffer.RemoveAt(0);
		}
		else
		{
			 inputActionType = InputBuffer[0].InputActionType;
			InputBuffer.RemoveAt(0);
			break;
		}
	}
	return inputActionType;
}

void UInputSubSystem::ClearInputBuffer()
{
	InputBuffer.Empty();
}

bool UInputSubSystem::ExecuteAction(EInputActionType InputActionType)
{
	OnInputActionExecuted.Broadcast(InputActionType);
	return true;
}
