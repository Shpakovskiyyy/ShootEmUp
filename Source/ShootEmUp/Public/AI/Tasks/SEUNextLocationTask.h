// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SEUNextLocationTask.generated.h"

UCLASS()
class SHOOTEMUP_API USEUNextLocationTask : public UBTTaskNode
{
    GENERATED_BODY()

public:
    USEUNextLocationTask();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float Radius = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector AimLocationKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    bool SetNewPointOnSelfCenter = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (EditCondition = "!SetNewPointOnSelfCenter"))
    FBlackboardKeySelector CenterActorKey;
    
};
