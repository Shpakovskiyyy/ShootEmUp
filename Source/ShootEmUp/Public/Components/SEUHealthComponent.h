// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SEUCoreTypes.h"
#include "SEUHealthComponent.generated.h"

class UCameraShakeBase;
class UPhysicalMaterial;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTEMUP_API USEUHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USEUHealthComponent();

    FOnDeathSignature OnDeath;
    FOnHealthChangedSignature OnHealthChanged;

    UFUNCTION(BlueprintCallable, Category = "Health")
    bool IsDead() const;

    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealthPercent() const { return Health / MaxHealth; }

    float GetHealth() const;

    bool TryToAddHealth(float BonusHealthAmount);
    bool IsHealthFull() const;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0", ClampMax = "100"))
    float MaxHealth = 100;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
    bool AutoHeal = true;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealUpdateTime = 1.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealDelay = 3.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealModifier = 2.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    TSubclassOf<UCameraShakeBase> CameraShakeEffect;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
    TMap<UPhysicalMaterial*, float> DamageMultipliers;

    virtual void BeginPlay() override;

private:
    float Health = 0.0f;

    FTimerHandle HealTimerHandle;

    UFUNCTION()
    void OnTakeAnyDamage(
        AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

    void HealUpdate();

    void SetHealth(float NewHealth);

    void PlayCameraShakeEffect();

    void Killed(AController* Killer);

    UFUNCTION()
    void OnTakePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation,
        class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection,
        const class UDamageType* DamageType, AActor* DamageCauser);

    UFUNCTION()
    void OnTakeRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin,
        FHitResult HitInfo, class AController* InstigatedBy, AActor* DamageCauser);

    void ApplyDamage(float Damage, AController* InstigatedBy);
    float GetPointDamageModifier(AActor* DamagedActor, const FName& BoneName);

    void ReportDamageEvent(float Damage, AController* InstigatedBy);
    
};
