// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SEUCharacterMovementComponent.generated.h"

UCLASS()
class SHOOTEMUP_API USEUCharacterMovementComponent : public UCharacterMovementComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "1.5", ClampMax = "5"))
    float RunModifier = 2.0f;

    virtual float GetMaxSpeed() const override;
    
};
