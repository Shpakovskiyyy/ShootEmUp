// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SEUDevDamageActor.generated.h"

UCLASS()
class SHOOTEMUP_API ASEUDevDamageActor : public AActor
{
    GENERATED_BODY()

public:
    ASEUDevDamageActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    USceneComponent* SceneComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Radius = 300.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FColor SphereColor = FColor::Emerald;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damage = 0.1f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool DoFullDamage = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UDamageType> DamageType;

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    
};
