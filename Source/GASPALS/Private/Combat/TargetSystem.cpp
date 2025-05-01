#include "Combat/TargetSystem.h"
#include "GameFramework/GameplayCameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"



UTargetSystem::UTargetSystem()
{
    CameraManager = nullptr;
    HardLockTarget = nullptr;
    bIsHardLocked = false;

    PrimaryComponentTick.bCanEverTick = true;

    DetectionSphere =  CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
    DetectionSphere->InitSphereRadius(1000.0f);
    DetectionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    DetectionSphere->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic); 
    DetectionSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    DetectionSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);  
    DetectionSphere->SetupAttachment(this);

    DetectionSphere->OnComponentBeginOverlap.AddDynamic(this, &UTargetSystem::OnBeginOverlap);
    DetectionSphere->OnComponentEndOverlap.AddDynamic(this, &UTargetSystem::OnEndOverlap);
}

void UTargetSystem::BeginPlay()
{
    Super::BeginPlay();
    UWorld * World = GetWorld();
    if (World != nullptr)
    {
        CameraManager = UGameplayStatics::GetPlayerCameraManager(World, 0);
    }
    
}

void UTargetSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

AActor* UTargetSystem::GetSoftLockTarget()
{
    if (CameraManager == nullptr)
    {
        return nullptr;
    }

    FVector CameraLocation = CameraManager->GetCameraLocation();
    FVector CameraForward = CameraManager->GetCameraRotation().Vector();

    //pollPotentialTargets();

    float closestAngle = MaxSoftLockAngle;
    float closestDistance = SoftLockRange;
    AActor* bestTarget = nullptr;

    for (AActor* Target : PotentialTargets)
    {
        if (Target == nullptr || Target == GetOwner())
        {
            continue;
        }

        FVector TargetLocation = Target->GetActorLocation();
        FVector DirectionToTarget = (TargetLocation - CameraLocation).GetSafeNormal();

        float Angle = FMath::Acos(FVector::DotProduct(CameraForward, DirectionToTarget)) * (180.0f / PI);

        if (Angle <= closestAngle && FVector::Dist(CameraLocation, TargetLocation) <= closestDistance)
        {
            closestAngle = Angle;
            closestDistance = FVector::Dist(CameraLocation, TargetLocation);
            bestTarget = Target;
        }
    }

    return bestTarget;
}

void UTargetSystem::ToggleHardLock()
{
    bIsHardLocked = !bIsHardLocked;

    if (CameraManager == nullptr)
    {
        return;
    }

    if (bIsHardLocked)
    {
        AActor* Target = FindLockOnTarget();

        // Check if a target was found, if not failed to hard lock
        if (Target == nullptr || Target == GetOwner())
        {
            bIsHardLocked = false;
            return;
        }

        HardLockTarget = Target;
    }
    else
    {
        HardLockTarget = nullptr;
    }
}

void UTargetSystem::SetHardLockTarget(AActor* Target)
{
    if (Target == nullptr || Target == GetOwner())
    {
        return;
    }

    HardLockTarget = Target;
    bIsHardLocked = true;
}

AActor* UTargetSystem::GetHardLockTarget()
{
    return HardLockTarget;
}

AActor* UTargetSystem::FindLockOnTarget()
{
    if (CameraManager == nullptr)
    {
        return nullptr;
    }

    FVector CameraLocation = CameraManager->GetCameraLocation();
    FVector CameraForward = CameraManager->GetCameraRotation().Vector();
    //pollPotentialTargets();
    if (PotentialTargets.Num() == 0)
    {
        return nullptr;
    }

    float LockOnRange = this->bIsHardLocked ? this->HardLockRange : SoftLockRange;
    float MaxAngle = this->bIsHardLocked ? this->HardLockAngle : MaxSoftLockAngle;

    float closestAngle = MaxAngle;
    float closestDistance = LockOnRange;
    AActor* bestTarget = nullptr;

    for (AActor* Target : PotentialTargets)
    {
        if (Target == nullptr || Target == GetOwner())
        {
            continue;
        }

        FVector TargetLocation = Target->GetActorLocation();
        FVector DirectionToTarget = (TargetLocation - CameraLocation).GetSafeNormal();

        float Angle = FMath::Acos(FVector::DotProduct(CameraForward, DirectionToTarget)) * (180.0f / PI);

        if (Angle <= closestAngle && FVector::Dist(CameraLocation, TargetLocation) <= closestDistance)
        {
            closestAngle = Angle;
            closestDistance = FVector::Dist(CameraLocation, TargetLocation);
            bestTarget = Target;
        }
    }

    return bestTarget;
}

void UTargetSystem::ClearHardLockTarget()
{
    bIsHardLocked = false;
    HardLockTarget = nullptr;
}

void UTargetSystem::pollPotentialTargets()
{
    if (CameraManager == nullptr)
    {
        return;
    }

    FVector CameraLocation = CameraManager->GetCameraLocation();
    FVector CameraForward = CameraManager->GetCameraRotation().Vector();

    float LockOnRange = this->bIsHardLocked ? this->HardLockRange : this->SoftLockRange;
    FVector TraceStart = CameraLocation;
    FVector TraceEnd = CameraLocation + (CameraForward * LockOnRange);
    float SphereRadius = LockOnRange;

    TArray<FHitResult> HitResults;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner()); // Ignore the player character

    bool bHit = GetWorld()->SweepMultiByChannel(
        HitResults,
        TraceStart,
        TraceEnd,
        FQuat::Identity,
        ECC_Pawn,
        FCollisionShape::MakeSphere(SphereRadius),
        CollisionParams
    );

    DrawDebugSphere(GetWorld(), TraceStart, SphereRadius, 12, FColor::Green, false, 1.0f);
    DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Blue, false, 1.0f, 0, 2.0f);

    PotentialTargets.Empty();

    if (bHit)
    {
        for (const FHitResult& Hit : HitResults)
        {
            AActor* HitActor = Hit.GetActor();
            if (HitActor && HitActor != GetOwner())
            {
                if (HitActor->ActorHasTag(FName("Enemy")))
                {
                    PotentialTargets.Add(HitActor);
                    
                    UE_LOG(LogTemp, Log, TEXT("Potential Target Found: %s"), *HitActor->GetName());
                }
            }
        }
    }
    UE_LOG(LogTemp, Log, TEXT("Total Potential Targets: %d"), PotentialTargets.Num());
}

bool UTargetSystem::CheckTargetInRange(AActor* Target)
{
    if (CameraManager == nullptr || Target == nullptr)
    {
        return false;
    }

    FVector CameraLocation = CameraManager->GetCameraLocation();
    FVector CameraForward = CameraManager->GetCameraRotation().Vector();

    float LockOnRange = this->bIsHardLocked ? this->HardLockRange : this->SoftLockRange;
    float MaxAngle = this->bIsHardLocked ? this->HardLockAngle : this->MaxSoftLockAngle;

    FVector TargetLocation = Target->GetActorLocation();
    FVector DirectionToTarget = (TargetLocation - CameraLocation).GetSafeNormal();

    float Angle = FMath::Acos(FVector::DotProduct(CameraForward, DirectionToTarget)) * (180.0f / PI);

    if (Angle <= MaxAngle && FVector::Dist(CameraLocation, TargetLocation) <= LockOnRange)
    {
        return true;
    }

    return false;
}

void UTargetSystem::OnBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    if(OtherActor && OtherActor != GetOwner())
    {
        PotentialTargets.AddUnique(OtherActor);
        UE_LOG(LogTemp, Log, TEXT("Potential Target Found: %s"), *OtherActor->GetName());
    }
}

void UTargetSystem::OnEndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
    if(OtherActor && OtherActor != GetOwner())
    {
        PotentialTargets.Remove(OtherActor);
        UE_LOG(LogTemp, Log, TEXT("Potential Target Lost: %s"), *OtherActor->GetName());
    }
}
