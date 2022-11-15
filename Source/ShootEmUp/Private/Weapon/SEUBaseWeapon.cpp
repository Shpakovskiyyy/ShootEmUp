// Shoot Em Up. Educational Project

#include "Weapon/SEUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "NiagaraFunctionLibrary.h"
#include "Niagara/Public/NiagaraComponent.h"

ASEUBaseWeapon::ASEUBaseWeapon()
{
    PrimaryActorTick.bCanEverTick = false;
    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

void ASEUBaseWeapon::StartShooting()
{
}

void ASEUBaseWeapon::StopShooting()
{
}

void ASEUBaseWeapon::BeginPlay()
{
    Super::BeginPlay();

    check(WeaponMesh);
    checkf(DefaultAmmoData.BulletsCount > 0, TEXT("Bullets count could not be less or equal zero!"));
    checkf(DefaultAmmoData.Magazines > 0, TEXT("Magazines count could not be less or equal zero!"));

    CurrentAmmoData = DefaultAmmoData;
}

void ASEUBaseWeapon::Shoot()
{
}

bool ASEUBaseWeapon::GetPlayerViewPoint(FVector& OutViewPointLocation, FRotator& OutViewPointRotation) const
{
    const auto SEUCharacter = Cast<ACharacter>(GetOwner());
    if(!SEUCharacter) return false;

    if(SEUCharacter->IsPlayerControlled())
    {
        const auto Controller = SEUCharacter->GetController<APlayerController>();
        if (!Controller) return false;

        Controller->GetPlayerViewPoint(OutViewPointLocation, OutViewPointRotation);
    }
    else
    {
        OutViewPointLocation = GetMuzzleSocketWorldLocation();
        OutViewPointRotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);
    }

    return true;
}

FVector ASEUBaseWeapon::GetMuzzleSocketWorldLocation() const
{
    return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool ASEUBaseWeapon::GetTracePoints(FVector& OutTraceStart, FVector& OutTraceEnd) const
{
    FVector ViewPointLocation;
    FRotator ViewPointRotation;
    if (!GetPlayerViewPoint(ViewPointLocation, ViewPointRotation)) return false;

    const FVector ShootDirection = ViewPointRotation.Vector();
    OutTraceStart = ViewPointLocation;
    OutTraceEnd = OutTraceStart + ShootDirection * TraceMaxLength;
    
    return true;
}

void ASEUBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const
{
    if (!GetWorld()) return;

    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());
    CollisionParams.bReturnPhysicalMaterial = true;

    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

void ASEUBaseWeapon::DecreaseAmmo()
{
    if (CurrentAmmoData.Magazines == 0) return;
    --CurrentAmmoData.BulletsCount;

    if (IsMagazineEmpty() && !IsAmmoEmpty())
    {
        StopShooting();
        OnMagazineEmpty.Broadcast(this);
    }
}

bool ASEUBaseWeapon::IsAmmoEmpty() const
{
    return CurrentAmmoData.IsFinite && CurrentAmmoData.Magazines == 0 && IsMagazineEmpty();
}

bool ASEUBaseWeapon::IsMagazineEmpty() const
{
    return CurrentAmmoData.BulletsCount == 0;
}

bool ASEUBaseWeapon::IsAmmoFull() const
{
    return CurrentAmmoData.Magazines == DefaultAmmoData.Magazines && CurrentAmmoData.BulletsCount == DefaultAmmoData.BulletsCount;
}

UNiagaraComponent* ASEUBaseWeapon::SpawnMuzzleFlash()
{
    return UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFlash, //
        WeaponMesh,                                                  //
        MuzzleSocketName,                                            //
        FVector::ZeroVector,                                         //
        FRotator::ZeroRotator,                                       //
        EAttachLocation::SnapToTarget, true);                        //
}

void ASEUBaseWeapon::ChangeMagazine()
{
    if(CurrentAmmoData.IsFinite)
    {
        if(CurrentAmmoData.Magazines == 0) return;
        --CurrentAmmoData.Magazines;
    }
    CurrentAmmoData.BulletsCount = DefaultAmmoData.BulletsCount;
}

bool ASEUBaseWeapon::CanReload() const
{
    return CurrentAmmoData.BulletsCount < DefaultAmmoData.BulletsCount && CurrentAmmoData.Magazines > 0;
}

bool ASEUBaseWeapon::TryToAddAmmo(int32 BonusMagazinesAmount)
{
    if(!CurrentAmmoData.IsFinite || IsAmmoFull() || BonusMagazinesAmount <= 0) return false;

    if(IsAmmoEmpty())
    {
        CurrentAmmoData.Magazines = FMath::Clamp(BonusMagazinesAmount, 0, DefaultAmmoData.Magazines + 1);
        OnMagazineEmpty.Broadcast(this);
    }
    else if(CurrentAmmoData.Magazines < DefaultAmmoData.Magazines)
    {
        const auto NextClipsAmount = CurrentAmmoData.Magazines + BonusMagazinesAmount;
        if(DefaultAmmoData.Magazines - NextClipsAmount >= 0)
        {
            CurrentAmmoData.Magazines = NextClipsAmount;
        }
        else
        {
            CurrentAmmoData.Magazines = DefaultAmmoData.Magazines;
            CurrentAmmoData.BulletsCount = DefaultAmmoData.BulletsCount;
        }
    }
    else
    {
        CurrentAmmoData.BulletsCount = DefaultAmmoData.BulletsCount;
    }

    return true;
}
