// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SEUChangeWeaponService.generated.h"

UCLASS()
class SHOOTEMUP_API USEUChangeWeaponService : public UBTService
{
    GENERATED_BODY()

public:
    USEUChangeWeaponService();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float Probability = 0.5f;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
    
};
