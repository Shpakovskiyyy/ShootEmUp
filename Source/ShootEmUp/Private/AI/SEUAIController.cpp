// Shoot Em Up. Educational Project

#include "AI/SEUAIController.h"
#include "AI/SEUAICharacter.h"
#include "Components/SEUAIPerceptionComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SEURespawnComponent.h"

ASEUAIController::ASEUAIController()
{
    AIPerceptionComponent = CreateDefaultSubobject<USEUAIPerceptionComponent>("AIPerceptionComponent");
    SetPerceptionComponent(*AIPerceptionComponent);

    RespawnComponent = CreateDefaultSubobject<USEURespawnComponent>("RespawnComponent");
    
    bWantsPlayerState = true;
}

void ASEUAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const auto SEUCharacter = Cast<ASEUAICharacter>(InPawn);
    if(SEUCharacter)
    {
        RunBehaviorTree(SEUCharacter->BehaviorTreeAsset);
    }
}

void ASEUAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    const auto ActorToAimTo = GetFocusOnActor();
    SetFocus(ActorToAimTo);
}

AActor* ASEUAIController::GetFocusOnActor() const
{
    if(!GetBlackboardComponent()) return nullptr;
    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
