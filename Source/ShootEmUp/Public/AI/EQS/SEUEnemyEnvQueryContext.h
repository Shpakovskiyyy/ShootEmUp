// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "SEUEnemyEnvQueryContext.generated.h"

UCLASS()
class SHOOTEMUP_API USEUEnemyEnvQueryContext : public UEnvQueryContext
{
    GENERATED_BODY()
public:
    virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FName EnemyActorKeyName = "EnemyActor";
    
};
