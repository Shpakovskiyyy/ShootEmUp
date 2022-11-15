// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SEUMenuPlayerController.generated.h"

UCLASS()
class SHOOTEMUP_API ASEUMenuPlayerController : public APlayerController
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
    
};
