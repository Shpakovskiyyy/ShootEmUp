// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SEUBaseCharacter.generated.h"

class USEUHealthComponent;
class USEUWeaponComponent;
class USoundCue;

UCLASS()
class SHOOTEMUP_API ASEUBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ASEUBaseCharacter(const FObjectInitializer& ObjInit);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USEUHealthComponent* HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USEUWeaponComponent* WeaponComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* DeathAnimMontage;

    UPROPERTY(EditDefaultsOnly, Category = "Material")
    FName MaterialColorName = "Paint Color";

    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    float LifeSpanOnDeath = 5.f;

    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    FVector2D LandedDamageVelocity = FVector2D(900.f, 1200.f);

    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    FVector2D LandedDamage = FVector2D(10.f, 100.f);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* DeathSound;

    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    
    virtual void TurnOff() override;
    
    virtual void Reset() override;

    virtual void OnDeath();

    UFUNCTION(BlueprintCallable, Category = "Movement")
    virtual bool IsRunning() const;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetMovementDirection() const;

    void SetPlayerColor(const FLinearColor& NewColor);
    
    virtual void OnHealthChanged(float Health, float HealthDelta);

private:
    UFUNCTION()
    void OnGroundLanded(const FHitResult& Hit);
};
