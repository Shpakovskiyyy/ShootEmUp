// Shoot Em Up. Educational Project

#include "AI/Services/SEUFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "SEUUtils.h"
#include "Components/SEUAIPerceptionComponent.h"

USEUFindEnemyService::USEUFindEnemyService()
{
    NodeName = "Find Enemy";
}

void USEUFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if(Blackboard)
    {
        const auto Controller = OwnerComp.GetAIOwner();
        const auto PerceptionComponent = SEUUtils::GetSEUPlayerComponent<USEUAIPerceptionComponent>(Controller);
        if(PerceptionComponent)
        {
            Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
