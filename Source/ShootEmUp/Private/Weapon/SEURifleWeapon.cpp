// Shoot Em Up. Educational Project

#include "Weapon/SEURifleWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Components/SEUWeaponFXComponent.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "Player/SEUPlayerController.h"

ASEURifleWeapon::ASEURifleWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<USEUWeaponFXComponent>("WeaponFXComponent");
}

void ASEURifleWeapon::StartShooting()
{
    InitMuzzleFX();
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASEURifleWeapon::Shoot, TimeBetweenShots, true);
    Shoot();
}

void ASEURifleWeapon::StopShooting()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
    SetFXActive(false);
}

void ASEURifleWeapon::Zoom(bool IsEnabled)
{
    const auto Controller = Cast<ASEUPlayerController>(GetController());
    if(!Controller || !Controller->PlayerCameraManager) return;

    if(IsEnabled)
    {
        DefaultCameraFOV = Controller->PlayerCameraManager->GetFOVAngle();
    }
    
    Controller->PlayerCameraManager->SetFOV(IsEnabled ? FOVZoom : DefaultCameraFOV);
}

void ASEURifleWeapon::BeginPlay()
{
    Super::BeginPlay();
}

void ASEURifleWeapon::Shoot()
{
    if(!GetWorld() || IsAmmoEmpty()) 
    {
        StopShooting();
        return;
    }

    FVector TraceStart;
    FVector TraceEnd;
    if(!GetTracePoints(TraceStart, TraceEnd))
    {
        StopShooting();
        return;
    }

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    FVector TraceEffectEnd = TraceEnd;
    if(HitResult.bBlockingHit)
    {
        TraceEffectEnd = HitResult.ImpactPoint;
        DealDamage(HitResult);
        WeaponFXComponent->PlayImpactFX(HitResult);
    }

    SpawnTraceEffect(GetMuzzleSocketWorldLocation(), TraceEffectEnd);
    DecreaseAmmo();
}

bool ASEURifleWeapon::GetTracePoints(FVector& OutTraceStart, FVector& OutTraceEnd) const
{
    FVector ViewPointLocation;
    FRotator ViewPointRotation;
    if(!GetPlayerViewPoint(ViewPointLocation, ViewPointRotation)) return false;

    const auto HalfRad = FMath::DegreesToRadians(ConeBulletSpread);
    const FVector ShootDirection = FMath::VRandCone(ViewPointRotation.Vector(), HalfRad);
    OutTraceStart = ViewPointLocation; 
    OutTraceEnd = OutTraceStart + ShootDirection * TraceMaxLength;
    return true;
}

void ASEURifleWeapon::DealDamage(const FHitResult& HitResult)
{
    const auto HitActor = HitResult.GetActor();
    if(!HitActor) return;

    FPointDamageEvent PointDamageEvent;
    PointDamageEvent.HitInfo = HitResult;
    
    HitActor->TakeDamage(BaseDamage, PointDamageEvent, GetController(), this);
}

void ASEURifleWeapon::InitMuzzleFX()
{
    if(!MuzzleFlashComponent)
    {
        MuzzleFlashComponent = SpawnMuzzleFlash();
    }

    if(!FireAudioComponent)
    {
        FireAudioComponent = UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
    }
    
    SetFXActive(true);
}

void ASEURifleWeapon::SetFXActive(bool IsActive)
{
    if(MuzzleFlashComponent)
    {
        MuzzleFlashComponent->SetPaused(!IsActive);
        MuzzleFlashComponent->SetVisibility(IsActive, true);
    }

    if(FireAudioComponent)
    {
        IsActive ? FireAudioComponent->Play() : FireAudioComponent->Stop();
    }
}

void ASEURifleWeapon::SpawnTraceEffect(const FVector& TraceStart, const FVector& TraceEnd)
{
    const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceEffect, TraceStart);
    if(TraceFXComponent)
    {
        TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
    }
}

AController* ASEURifleWeapon::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}
