// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SEUBasePickup.generated.h"

class USphereComponent;
class USoundCue;

UCLASS()
class SHOOTEMUP_API ASEUBasePickup : public AActor
{
    GENERATED_BODY()

public:
    ASEUBasePickup();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    USphereComponent* CollisionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    float RespawnTime = 5.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    USoundCue* TakenSound;

    virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
    virtual void Tick(float DeltaTime) override;

    bool CouldBeTaken() const;

private:
    float RotationYaw = 0.f;
    FTimerHandle RespawnTimerHandle;

    virtual bool GivePickupTo(APawn* PlayerPawn);
    void PickupTaken();
    void Respawn();
    void GenerateRotationYaw();
    
};
