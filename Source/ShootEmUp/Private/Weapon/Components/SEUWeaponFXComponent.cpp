// Shoot Em Up. Educational Project

#include "Weapon/Components/SEUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Sound/SoundCue.h"

USEUWeaponFXComponent::USEUWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USEUWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	auto ImpactData = DefaultImpactData;

	if(Hit.PhysMaterial.IsValid())
	{
	    const auto PhysicsMaterial = Hit.PhysMaterial.Get();
	    if(ImpactDataMap.Contains(PhysicsMaterial))
	    {
	        ImpactData = ImpactDataMap[PhysicsMaterial];
	    }
	}

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),   //
		ImpactData.NiagaraEffect,                              //
		Hit.ImpactPoint,                                       //
		Hit.ImpactNormal.Rotation());                          //

	auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),   //
		ImpactData.DecalData.Material,                                       //
		ImpactData.DecalData.Size,                                           //
		Hit.ImpactPoint,                                                     //
		Hit.ImpactNormal.Rotation());                                        //

	if(DecalComponent)
	{
	    DecalComponent->SetFadeOut(ImpactData.DecalData.Lifetime, ImpactData.DecalData.FadeoutTime);
	}

    UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactData.Sound, Hit.ImpactPoint);
}


