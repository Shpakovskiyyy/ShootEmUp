// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SEUBaseWeapon.h"
#include "SEURifleWeapon.generated.h"

class USEUWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UAudioComponent;

UCLASS()
class SHOOTEMUP_API ASEURifleWeapon : public ASEUBaseWeapon
{
    GENERATED_BODY()

public:
    ASEURifleWeapon();

    virtual void StartShooting() override;
    virtual void StopShooting() override;

    virtual void Zoom(bool IsEnabled) override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TimeBetweenShots = 0.1f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float ConeBulletSpread = 1.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 5.f, ClampMax = 20.f), Category = "Damage")
    float BaseDamage = 10.f;

    UPROPERTY(VisibleAnywhere, Category = "VFX")
    USEUWeaponFXComponent* WeaponFXComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* TraceEffect;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FString TraceTargetName = "TraceTarget";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float FOVZoom = 50.f;

    virtual void BeginPlay() override;
    virtual void Shoot() override;
    virtual bool GetTracePoints(FVector& OutTraceStart, FVector& OutTraceEnd) const override;

private:
    FTimerHandle ShotTimerHandle;
    
    UPROPERTY()
    UNiagaraComponent* MuzzleFlashComponent;

    UPROPERTY()
    UAudioComponent* FireAudioComponent;

    float DefaultCameraFOV = 90.f;

private:
    void DealDamage(const FHitResult& HitResult);

    void InitMuzzleFX();
    void SetFXActive(bool IsActive);

    void SpawnTraceEffect(const FVector& TraceStart, const FVector& TraceEnd);
    AController* GetController() const;
    
};
