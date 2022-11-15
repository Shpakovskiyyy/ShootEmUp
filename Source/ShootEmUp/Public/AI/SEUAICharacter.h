// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "Player/SEUBaseCharacter.h"
#include "SEUAICharacter.generated.h"

class UBehaviorTree;
class UWidgetComponent;

UCLASS()
class SHOOTEMUP_API ASEUAICharacter : public ASEUBaseCharacter
{
    GENERATED_BODY()

public:
    ASEUAICharacter(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* BehaviorTreeAsset;

    virtual void Tick(float DeltaSeconds) override;
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UWidgetComponent* HealthBarWidgetComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    float HealthBarRenderDistance = 1000.f;

    virtual void BeginPlay() override;
    
    virtual void OnDeath() override;
    virtual void OnHealthChanged(float Health, float HealthDelta) override;

private:
    void UpdateHealthBarVisibility();
    
};
