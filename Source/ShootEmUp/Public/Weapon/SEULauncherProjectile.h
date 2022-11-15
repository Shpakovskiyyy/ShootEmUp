// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SEULauncherProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class USEUWeaponFXComponent;

UCLASS()
class SHOOTEMUP_API ASEULauncherProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	ASEULauncherProjectile();

	void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; } 

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	USphereComponent* CollisionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float DamageRadius = 200.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float Damage = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool DoFullDamage = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float LifeSpanSeconds = 10.f;

	UPROPERTY(VisibleAnywhere, Category = "VFX")
    USEUWeaponFXComponent* WeaponFXComponent;

protected:
	virtual void BeginPlay() override;

private:
	FVector ShotDirection;

private:
	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	AController* GetController() const;

};