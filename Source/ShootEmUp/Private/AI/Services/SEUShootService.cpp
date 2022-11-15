// Shoot Em Up. Educational Project

#include "AI/Services/SEUShootService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Weapon/SEUWeaponComponent.h"
#include "SEUUtils.h"

USEUShootService::USEUShootService()
{
    NodeName = "Shoot";
}

void USEUShootService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

    if(Controller)
    {
        const auto WeaponComponent = SEUUtils::GetSEUPlayerComponent<USEUWeaponComponent>(Controller->GetPawn());
        if(WeaponComponent)
        {
            HasAim ? WeaponComponent->StartShooting() : WeaponComponent->StopShooting();
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
