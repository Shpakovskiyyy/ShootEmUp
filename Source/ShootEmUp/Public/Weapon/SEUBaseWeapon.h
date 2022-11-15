// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SEUCoreTypes.h"
#include "SEUBaseWeapon.generated.h"

class USkeletalMeshComponent;
class UNiagaraSystem;
class UNiagaraComponent;
class USoundCue;

UCLASS()
class SHOOTEMUP_API ASEUBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    ASEUBaseWeapon();

    FOnMagazineEmptySignature OnMagazineEmpty;

    virtual void StartShooting();
    virtual void StopShooting();
    
    void ChangeMagazine();
    bool CanReload() const;

    FWeaponUIData GetUIData() const { return UIData; }
    FAmmoData GetAmmoData() const { return CurrentAmmoData; }

    bool TryToAddAmmo(int32 BonusMagazinesAmount);
    bool IsAmmoEmpty() const;
    bool IsAmmoFull() const;

    virtual void Zoom(bool IsEnabled) {}

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FName MuzzleSocketName = "MuzzleFlashSocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TraceMaxLength = 1500.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FAmmoData DefaultAmmoData{20, 10, true};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FWeaponUIData UIData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* MuzzleFlash;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* FireSound;

    virtual void BeginPlay() override;

    virtual void Shoot();
    
    bool GetPlayerViewPoint(FVector& OutViewPointLocation, FRotator& OutViewPointRotation) const;
    FVector GetMuzzleSocketWorldLocation() const;
    virtual bool GetTracePoints(FVector& OutTraceStart, FVector& OutTraceEnd) const;
    
    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const;

    void DecreaseAmmo();
    bool IsMagazineEmpty() const;
    
    UNiagaraComponent* SpawnMuzzleFlash();

private:
    FAmmoData CurrentAmmoData;
};
