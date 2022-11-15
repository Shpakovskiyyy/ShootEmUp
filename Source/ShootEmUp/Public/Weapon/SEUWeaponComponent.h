// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SEUCoreTypes.h"
#include "SEUWeaponComponent.generated.h"

class ASEUBaseWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTEMUP_API USEUWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USEUWeaponComponent();

    virtual void StartShooting();
    void StopShooting();
    virtual void NextWeapon();
    void Reload();

    bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;
    bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

    bool TryToAddAmmo(TSubclassOf<ASEUBaseWeapon> WeaponType, int32 BonusMagazinesAmount);
    bool NeedAmmo(TSubclassOf<ASEUBaseWeapon> WeaponType) const;

    void Zoom(bool IsEnabled);

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    bool CanFire() const;
    bool CanEquip() const;

    void EquipWeapon(const int32 WeaponIndex);

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<FWeaponData> WeaponData;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponEquipSocketName = "WeaponSocket";

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* EquipAnimMontage;

    UPROPERTY()
    ASEUBaseWeapon* CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<ASEUBaseWeapon*> Weapons;

    int32 CurrentWeaponIndex = 0;

private:
    UPROPERTY()
    UAnimMontage* CurrentReloadAnimMontage = nullptr;

    bool EquipAnimInProgress = false;
    bool ReloadAnimInProgress = false;

    void SpawnWeapons();
    void AttachWeaponToSocket(ASEUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

    void PlayAnimMontage(UAnimMontage* Animation) const;
    void InitAnimations();
    void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
    void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

    bool CanReload() const;

    void OnEmptyMagazine(ASEUBaseWeapon* AmmoEmptyWeapon);
    void ChangeMagazine();
    
};
