// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SEUShootService.generated.h"

UCLASS()
class SHOOTEMUP_API USEUShootService : public UBTService
{
    GENERATED_BODY()

public:
    USEUShootService();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector EnemyActorKey;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
    
};
