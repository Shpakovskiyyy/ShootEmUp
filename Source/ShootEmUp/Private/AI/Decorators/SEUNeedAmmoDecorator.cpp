// Shoot Em Up. Educational Project

#include "AI/Decorators/SEUNeedAmmoDecorator.h"
#include "AIController.h"
#include "SEUUtils.h"
#include "Weapon/SEUWeaponComponent.h"

USEUNeedAmmoDecorator::USEUNeedAmmoDecorator()
{
    NodeName = "Need Ammo";
}

bool USEUNeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if(!Controller) return false;

    const auto WeaponComponent = SEUUtils::GetSEUPlayerComponent<USEUWeaponComponent>(Controller->GetPawn());
    if(!WeaponComponent) return false;

    return WeaponComponent->NeedAmmo(WeaponType);
}
