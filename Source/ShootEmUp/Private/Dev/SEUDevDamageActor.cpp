// Shoot Em Up. Educational Project

#include "Dev/SEUDevDamageActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ASEUDevDamageActor::ASEUDevDamageActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
}

void ASEUDevDamageActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASEUDevDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, SphereColor);

	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, DamageType, {}, this, nullptr, DoFullDamage);
}

