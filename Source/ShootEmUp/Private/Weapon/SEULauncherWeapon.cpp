// Shoot Em Up. Educational Project

#include "Weapon/SEULauncherWeapon.h"
#include "Weapon/SEULauncherProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void ASEULauncherWeapon::StartShooting()
{
    Shoot();
}

void ASEULauncherWeapon::Shoot()
{
    if(!GetWorld()) return;

    if(IsAmmoEmpty())
    {
        UGameplayStatics::SpawnSoundAtLocation(GetWorld(), NoAmmoSound, GetActorLocation());
        return;
    }

    FVector TraceStart, TraceEnd;
    if(!GetTracePoints(TraceStart, TraceEnd)) return;

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    const FVector Direction = (EndPoint - GetMuzzleSocketWorldLocation()).GetSafeNormal();

    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleSocketWorldLocation());
    
    ASEULauncherProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASEULauncherProjectile>(ProjectileClass, SpawnTransform);
    if(Projectile)
    {
        Projectile->SetShotDirection(Direction);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    }

    DecreaseAmmo();
    SpawnMuzzleFlash();
    UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
}
