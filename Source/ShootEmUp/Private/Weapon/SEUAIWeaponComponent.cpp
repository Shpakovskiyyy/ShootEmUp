// Shoot Em Up. Educational Project

#include "Weapon/SEUAIWeaponComponent.h"
#include "Weapon/SEUBaseWeapon.h"

void USEUAIWeaponComponent::StartShooting()
{
    if(!CanFire()) return;

    if(CurrentWeapon->IsAmmoEmpty())
    {
        NextWeapon();
    }
    else
    {
        CurrentWeapon->StartShooting();
    }
}

void USEUAIWeaponComponent::NextWeapon()
{
    if(!CanEquip()) return;

    int32 NextWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    while (NextWeaponIndex != CurrentWeaponIndex)
    {
        if(!Weapons[NextWeaponIndex]->IsAmmoEmpty()) break;
        NextWeaponIndex = (NextWeaponIndex + 1) % Weapons.Num();
    }

    if(CurrentWeaponIndex != NextWeaponIndex)
    {
        CurrentWeaponIndex = NextWeaponIndex;
        EquipWeapon(CurrentWeaponIndex);
    }
}
