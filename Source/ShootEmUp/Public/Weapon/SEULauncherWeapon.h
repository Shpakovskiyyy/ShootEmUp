// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SEUBaseWeapon.h"
#include "SEULauncherWeapon.generated.h"

class ASEULauncherProjectile;
class USoundCue;

UCLASS()
class SHOOTEMUP_API ASEULauncherWeapon : public ASEUBaseWeapon
{
    GENERATED_BODY()

public:
    virtual void StartShooting() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ASEULauncherProjectile> ProjectileClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* NoAmmoSound;

    virtual void Shoot() override;
};
