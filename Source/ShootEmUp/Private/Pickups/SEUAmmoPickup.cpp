// Shoot Em Up. Educational Project

#include "Pickups/SEUAmmoPickup.h"
#include "Components/SEUHealthComponent.h"
#include "Weapon/SEUWeaponComponent.h"
#include "SEUUtils.h"

bool ASEUAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthComponent = SEUUtils::GetSEUPlayerComponent<USEUHealthComponent>(PlayerPawn);
    if(!HealthComponent || HealthComponent->IsDead()) return false;

    const auto WeaponComponent = SEUUtils::GetSEUPlayerComponent<USEUWeaponComponent>(PlayerPawn);
    if(!WeaponComponent) return false;

    return WeaponComponent->TryToAddAmmo(WeaponType, BonusMagazinesAmount);
}
