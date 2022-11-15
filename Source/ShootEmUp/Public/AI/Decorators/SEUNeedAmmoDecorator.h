// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "SEUNeedAmmoDecorator.generated.h"

class ASEUBaseWeapon;

UCLASS()
class SHOOTEMUP_API USEUNeedAmmoDecorator : public UBTDecorator
{
    GENERATED_BODY()

public:
    USEUNeedAmmoDecorator();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TSubclassOf<ASEUBaseWeapon> WeaponType;

    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
    
};
