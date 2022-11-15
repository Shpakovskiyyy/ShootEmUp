// Shoot Em Up. Educational Project

#include "AI/Services/SEUChangeWeaponService.h"
#include "Weapon/SEUWeaponComponent.h"
#include "AIController.h"
#include "ParameterCollection.h"
#include "SEUUtils.h"

USEUChangeWeaponService::USEUChangeWeaponService()
{
    NodeName = "Change Weapon";
}

void USEUChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    if(Controller)
    {
        const auto WeaponComponent = SEUUtils::GetSEUPlayerComponent<USEUWeaponComponent>(Controller->GetPawn());
        if(WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
        {
            WeaponComponent->NextWeapon();
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
