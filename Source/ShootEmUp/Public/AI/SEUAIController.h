// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SEUAIController.generated.h"

class USEUAIPerceptionComponent;
class USEURespawnComponent;

UCLASS()
class SHOOTEMUP_API ASEUAIController : public AAIController
{
    GENERATED_BODY()

public:
    ASEUAIController();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USEUAIPerceptionComponent* AIPerceptionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FName FocusOnKeyName = "EnemyActor";

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USEURespawnComponent* RespawnComponent;

    virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float DeltaSeconds) override;

private:
    AActor* GetFocusOnActor() const;
    
};
