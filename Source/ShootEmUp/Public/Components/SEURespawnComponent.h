// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SEURespawnComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTEMUP_API USEURespawnComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USEURespawnComponent();
    
    void Respawn(const int32 RespawnTime);

    int32 GetRespawnTimeCountDown() const { return RespawnTimeCountDown; }
    bool IsRespawnInProgress() const;

private:
    FTimerHandle RespawnTimerHandle;
    int32 RespawnTimeCountDown;

    void RespawnTimerUpdate();
    
};
