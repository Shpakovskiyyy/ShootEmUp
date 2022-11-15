// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "Pickups/SEUBasePickup.h"
#include "SEUHealthPickup.generated.h"

UCLASS()
class SHOOTEMUP_API ASEUHealthPickup : public ASEUBasePickup
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "100.0"))
	float BonusHealthAmount = 100.f;

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;

};
