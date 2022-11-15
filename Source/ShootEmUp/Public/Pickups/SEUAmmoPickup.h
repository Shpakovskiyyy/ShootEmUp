// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "Pickups/SEUBasePickup.h"
#include "SEUAmmoPickup.generated.h"

class ASEUBaseWeapon;

UCLASS()
class SHOOTEMUP_API ASEUAmmoPickup : public ASEUBasePickup
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0"))
	int32 BonusMagazinesAmount = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	TSubclassOf<ASEUBaseWeapon> WeaponType;

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
    
};
