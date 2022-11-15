// Shoot Em Up. Educational Project

#include "AI/Decorators/SEUHealthPercentDecorator.h"
#include "AIController.h"
#include "SEUUtils.h"
#include "Components/SEUHealthComponent.h"

USEUHealthPercentDecorator::USEUHealthPercentDecorator()
{
    NodeName = "Health Percent";
}

bool USEUHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if(!Controller) return false;

    const auto HealthComponent = SEUUtils::GetSEUPlayerComponent<USEUHealthComponent>(Controller->GetPawn());
    if(!HealthComponent || HealthComponent->IsDead()) return false;

    return HealthComponent->GetHealthPercent() <= HealthPercent;
}
