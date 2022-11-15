// Shoot Em Up. Educational Project

#include "Components/SEUAIPerceptionComponent.h"
#include "AI/SEUAIController.h"
#include "SEUUtils.h"
#include "Components/SEUHealthComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Damage.h"

AActor* USEUAIPerceptionComponent::GetClosestEnemy() const
{
    TArray<AActor*> PercievedActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercievedActors);
    if(PercievedActors.Num() == 0)
    {
        GetCurrentlyPerceivedActors(UAISense_Damage::StaticClass(), PercievedActors);
        if(PercievedActors.Num() == 0) return nullptr;
    } 

    const auto Controller = Cast<AAIController>(GetOwner());
    if(!Controller) return nullptr;

    const auto Pawn = Controller->GetPawn();
    if(!Pawn) return nullptr;

    float ClosestEnemyDistance = MAX_FLT;
    AActor* ClosestPawn = nullptr;
    for(const auto Actor : PercievedActors)
    {
        const auto HealthComponent = SEUUtils::GetSEUPlayerComponent<USEUHealthComponent>(Actor);
        const auto PercievedPawn = Cast<APawn>(Actor);
        const bool AreEnemies = PercievedPawn && SEUUtils::AreEnemies(Controller, PercievedPawn->Controller);
        
        if(HealthComponent && !HealthComponent->IsDead() && AreEnemies)
        {
            const auto CurrentDistance = (Actor->GetActorLocation() - Pawn->GetActorLocation()).Size();
            if(CurrentDistance < ClosestEnemyDistance) 
            {
                ClosestEnemyDistance = CurrentDistance;
                ClosestPawn = Actor; 
            }
        }
    }

    return ClosestPawn;
}
