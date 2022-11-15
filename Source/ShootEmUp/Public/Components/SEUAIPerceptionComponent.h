// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"

#include "SEUAIPerceptionComponent.generated.h"

UCLASS()
class SHOOTEMUP_API USEUAIPerceptionComponent : public UAIPerceptionComponent
{
    GENERATED_BODY()

public:
    AActor* GetClosestEnemy() const;
    
};
