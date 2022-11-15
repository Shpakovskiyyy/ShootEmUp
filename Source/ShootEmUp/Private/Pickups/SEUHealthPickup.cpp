// Shoot Em Up. Educational Project

#include "Pickups/SEUHealthPickup.h"
#include "Components/SEUHealthComponent.h"
#include "SEUUtils.h"

bool ASEUHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthComponent = SEUUtils::GetSEUPlayerComponent<USEUHealthComponent>(PlayerPawn);
    if(!HealthComponent) return false;

    return HealthComponent->TryToAddHealth(BonusHealthAmount);
}
