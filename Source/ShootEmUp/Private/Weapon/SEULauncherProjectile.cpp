// Shoot Em Up. Educational Project

#include "Weapon/SEULauncherProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Components/SEUWeaponFXComponent.h"

ASEULauncherProjectile::ASEULauncherProjectile()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
    CollisionComponent->InitSphereRadius(5.f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    CollisionComponent->bReturnMaterialOnMove = true;
    SetRootComponent(CollisionComponent);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
    MovementComponent->InitialSpeed = 5000.f;
    MovementComponent->ProjectileGravityScale = 0.f;

    WeaponFXComponent = CreateDefaultSubobject<USEUWeaponFXComponent>("WeaponFXComponent");
}

void ASEULauncherProjectile::BeginPlay()
{
    Super::BeginPlay();

    check(MovementComponent);
    check(CollisionComponent);
    check(WeaponFXComponent);

    MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
    CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
    CollisionComponent->OnComponentHit.AddDynamic(this, &ASEULauncherProjectile::OnProjectileHit);

    SetLifeSpan(LifeSpanSeconds);
}

void ASEULauncherProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    FVector NormalImpulse, const FHitResult& Hit)
{
    if (!GetWorld()) return;

    MovementComponent->StopMovementImmediately();

    UGameplayStatics::ApplyRadialDamage(GetWorld(),  // 
        Damage,                                      //
        GetActorLocation(),                          //
        DamageRadius,                                //
        UDamageType::StaticClass(),                  //
        {},                                          //
        this,                                        //
        GetController(),                             //
        DoFullDamage                                 //
        );

    WeaponFXComponent->PlayImpactFX(Hit); 
    Destroy();
}

AController* ASEULauncherProjectile::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}
