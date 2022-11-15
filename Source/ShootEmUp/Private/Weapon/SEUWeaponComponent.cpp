// Shoot Em Up. Educational Project

#include "Weapon/SEUWeaponComponent.h"
#include "Weapon/SEUBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/SEUEquipFinishedAimNotify.h"
#include "Animations/SEUReloadFinishedAnimNotify.h"
#include "Animations/AnimUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All)

USEUWeaponComponent::USEUWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USEUWeaponComponent::StartShooting()
{
    if (!CanFire()) return;
    CurrentWeapon->StartShooting();
}

void USEUWeaponComponent::StopShooting()
{
    if (!CurrentWeapon) return;
    CurrentWeapon->StopShooting();
}

void USEUWeaponComponent::NextWeapon()
{
    if (!CanEquip()) return;
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}

void USEUWeaponComponent::Reload()
{
    ChangeMagazine();
}

bool USEUWeaponComponent::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
    if(CurrentWeapon)
    {
        UIData = CurrentWeapon->GetUIData();
        return true;
    }

    return false;
}

bool USEUWeaponComponent::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
    if(CurrentWeapon)
    {
        AmmoData = CurrentWeapon->GetAmmoData();
        return true;
    }

    return false;
}

bool USEUWeaponComponent::TryToAddAmmo(TSubclassOf<ASEUBaseWeapon> WeaponType, int32 BonusMagazinesAmount)
{
    for(auto Weapon : Weapons)
    {
        if(Weapon && Weapon->IsA(WeaponType))
        {
            return Weapon->TryToAddAmmo(BonusMagazinesAmount);
        }
    }
    return false;
}

bool USEUWeaponComponent::NeedAmmo(TSubclassOf<ASEUBaseWeapon> WeaponType) const
{
    for(const auto Weapon : Weapons)
    {
        if(Weapon && Weapon->IsA(WeaponType))
        {
            return !Weapon->IsAmmoFull(); 
        }
    }
    return false;
}

void USEUWeaponComponent::Zoom(bool IsEnabled)
{
    if(CurrentWeapon)
    {
        CurrentWeapon->Zoom(IsEnabled);
    }
}

void USEUWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    checkf(WeaponData.Num() == 2, TEXT("Character can only hold 2 weapons")); 

    CurrentWeaponIndex = 0;

    InitAnimations();

    SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);
}

void USEUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CurrentWeapon = nullptr;
    for (auto Weapon : Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }
    Weapons.Empty();

    Super::EndPlay(EndPlayReason);
}

void USEUWeaponComponent::SpawnWeapons()
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if (!GetWorld() || !Character) return;

    for (auto OneWeaponData : WeaponData)
    {
        auto Weapon = GetWorld()->SpawnActor<ASEUBaseWeapon>(OneWeaponData.WeaponClass);
        if (!Weapon) continue;

        Weapon->OnMagazineEmpty.AddUObject(this, &USEUWeaponComponent::OnEmptyMagazine);
        Weapon->SetOwner(Character);
        Weapons.Add(Weapon);

        AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
    }
}

void USEUWeaponComponent::AttachWeaponToSocket(ASEUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
    if (!Weapon || !SceneComponent) return;

    const FAttachmentTransformRules AttachmentRules{ EAttachmentRule::SnapToTarget, false };
    Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void USEUWeaponComponent::EquipWeapon(const int32 WeaponIndex)
{
    if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
    {
        UE_LOG(LogWeaponComponent, Error, TEXT("Invalid weapon array index"));
        return;
    }

    const auto Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    if (CurrentWeapon)
    {
        CurrentWeapon->Zoom(false);
        CurrentWeapon->StopShooting();
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
    }

    CurrentWeapon = Weapons[WeaponIndex];
    const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data)
        {
            return Data.WeaponClass == CurrentWeapon->GetClass();
        });
    
    CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;
    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
    EquipAnimInProgress = true;
    PlayAnimMontage(EquipAnimMontage);
}

void USEUWeaponComponent::PlayAnimMontage(UAnimMontage* Animation) const
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    Character->PlayAnimMontage(Animation);
}

void USEUWeaponComponent::InitAnimations()
{
    auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<USEUEquipFinishedAimNotify>(EquipAnimMontage);
    if (EquipFinishedNotify)
    {
        EquipFinishedNotify->OnNotified.AddUObject(this, &USEUWeaponComponent::OnEquipFinished);
    }
    else
    {
        UE_LOG(LogWeaponComponent, Error, TEXT("Equip anim notify isn't set!"));
        checkNoEntry();
    }

    for (auto& OneWeaponData : WeaponData)
    {
        auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<USEUReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage);
        if (!ReloadFinishedNotify)
        {
            UE_LOG(LogWeaponComponent, Error, TEXT("Reload anim notify isn't set!"));
            checkNoEntry();
        }

        ReloadFinishedNotify->OnNotified.AddUObject(this, &USEUWeaponComponent::OnReloadFinished);
    }
}

void USEUWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if (!Character || MeshComponent != Character->GetMesh()) return;

    EquipAnimInProgress = false;
}

void USEUWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComponent)
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if (!Character || MeshComponent != Character->GetMesh()) return;

    ReloadAnimInProgress = false;
}

bool USEUWeaponComponent::CanFire() const
{
    return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool USEUWeaponComponent::CanEquip() const
{
    return !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool USEUWeaponComponent::CanReload() const
{
    return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress && CurrentWeapon->CanReload();
}

void USEUWeaponComponent::OnEmptyMagazine(ASEUBaseWeapon* AmmoEmptyWeapon)
{
    if(!AmmoEmptyWeapon) return;

    if(CurrentWeapon == AmmoEmptyWeapon)
    {
        ChangeMagazine();
    }
    else
    {
        for(auto Weapon : Weapons)
        {
            if(Weapon == AmmoEmptyWeapon)
            {
                Weapon->ChangeMagazine();
            }
        }
    }
}

void USEUWeaponComponent::ChangeMagazine()
{
    if (!CanReload()) return;
    CurrentWeapon->StopShooting();
    CurrentWeapon->ChangeMagazine();

    ReloadAnimInProgress = true;
    PlayAnimMontage(CurrentReloadAnimMontage);
}