// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "SEUHealthPercentDecorator.generated.h"

UCLASS()
class SHOOTEMUP_API USEUHealthPercentDecorator : public UBTDecorator
{
    GENERATED_BODY()

public:
    USEUHealthPercentDecorator();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float HealthPercent = 0.6f;

    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
    
};
