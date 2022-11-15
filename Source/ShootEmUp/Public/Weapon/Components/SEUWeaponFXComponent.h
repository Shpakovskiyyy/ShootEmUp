// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SEUCoreTypes.h"
#include "SEUWeaponFXComponent.generated.h"

class UNiagaraSystem;
class UPhysicalMaterial;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTEMUP_API USEUWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USEUWeaponFXComponent();

	void PlayImpactFX(const FHitResult& Hit);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FImpactData DefaultImpactData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TMap<UPhysicalMaterial*, FImpactData> ImpactDataMap;

};
