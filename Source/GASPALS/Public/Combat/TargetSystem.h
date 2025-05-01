
#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Camera/PlayerCameraManager.h"

#include "TargetSystem.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GASPALS_API UTargetSystem : public USceneComponent
{
    
    GENERATED_BODY()

public:


    // Sets default values for this component's properties
    UTargetSystem();

    void BeginPlay() override;

    void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable, Category = "Targeting")
    AActor* GetSoftLockTarget();

    UFUNCTION(BlueprintCallable, Category = "Targeting")
    void ToggleHardLock();

    UFUNCTION(BlueprintCallable, Category = "Targeting")
    void SetHardLockTarget(AActor* Target);

    UFUNCTION(BlueprintCallable, Category = "Targeting")
    AActor *FindLockOnTarget();

    UFUNCTION(BlueprintCallable, Category = "Targeting")
    AActor * GetHardLockTarget();

    UFUNCTION(BlueprintCallable, Category = "Targeting")
    void ClearHardLockTarget();

    UFUNCTION(BlueprintCallable, Category = "Targeting")
    void pollPotentialTargets();

    UFUNCTION(BlueprintCallable, Category = "Targeting")
    bool CheckTargetInRange(AActor* Target);

    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, 
                        const FHitResult& SweepResult);

    UFUNCTION()
    void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
  
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
    class USphereComponent *DetectionSphere;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
    APlayerCameraManager* CameraManager;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
    TArray<AActor*> PotentialTargets;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
    AActor* HardLockTarget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
    AActor* SoftLockTarget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
    bool bIsHardLocked = false;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
    bool bAllowSoftLock = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
    bool bAllowHardLockRetarget = true;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
    float MaxSoftLockAngle = 25.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
    float SoftLockRange = 1500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
    float HardLockRange = 1500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
    float HardLockAngle = 25.f;



};