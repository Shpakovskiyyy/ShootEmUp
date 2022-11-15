// Shoot Em Up. Educational Project

#include "Components/SEUHealthComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraShakeBase.h"
#include "SEUGameModeBase.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Perception/AISense_Damage.h"

USEUHealthComponent::USEUHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

bool USEUHealthComponent::IsDead() const
{
    return FMath::IsNearlyZero(Health);
}

float USEUHealthComponent::GetHealth() const
{
    return Health;
}

bool USEUHealthComponent::TryToAddHealth(float BonusHealthAmount)
{
    if (IsDead() || IsHealthFull()) return false;

    SetHealth(Health + BonusHealthAmount);
    return true;
}

bool USEUHealthComponent::IsHealthFull() const
{
    return FMath::IsNearlyEqual(Health, MaxHealth);
}

void USEUHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    check(MaxHealth > 0);

    SetHealth(MaxHealth);

    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USEUHealthComponent::OnTakeAnyDamage);
        ComponentOwner->OnTakePointDamage.AddDynamic(this, &USEUHealthComponent::OnTakePointDamage);
        ComponentOwner->OnTakeRadialDamage.AddDynamic(this, &USEUHealthComponent::OnTakeRadialDamage);
    }
}

void USEUHealthComponent::OnTakeAnyDamage
(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
    AController* InstigatedBy, AActor* DamageCauser)
{
}

void USEUHealthComponent::HealUpdate()
{
    SetHealth(Health + HealModifier);

    if (IsHealthFull() && GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    }
}

void USEUHealthComponent::SetHealth(float NewHealth)
{
    const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    const auto HealthDelta = NextHealth - Health;

    Health = NextHealth;
    OnHealthChanged.Broadcast(Health, HealthDelta);
}

void USEUHealthComponent::PlayCameraShakeEffect()
{
    if (IsDead()) return;

    const auto Player = Cast<APawn>(GetOwner());
    if (!Player) return;

    const auto Controller = Player->GetController<APlayerController>();
    if (!Controller || !Controller->PlayerCameraManager) return;

    Controller->PlayerCameraManager->StartCameraShake(CameraShakeEffect);
}

void USEUHealthComponent::Killed(AController* Killer)
{
    if (!GetWorld()) return;

    const auto GameMode = Cast<ASEUGameModeBase>(GetWorld()->GetAuthGameMode());
    if (!GameMode) return;

    const auto Player = Cast<APawn>(GetOwner());
    const auto Victim = Player ? Player->Controller : nullptr;

    GameMode->GotKilled(Killer, Victim);
}

void USEUHealthComponent::OnTakePointDamage
(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName,
    FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
    const auto FinalDamage = Damage * GetPointDamageModifier(DamagedActor, BoneName);
    ApplyDamage(FinalDamage, InstigatedBy);
}

void USEUHealthComponent::OnTakeRadialDamage
(AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin, FHitResult HitInfo, AController* InstigatedBy, AActor* DamageCauser)
{
    ApplyDamage(Damage, InstigatedBy);
}

void USEUHealthComponent::ApplyDamage(float Damage, AController* InstigatedBy)
{
    if (Damage <= 0.0f || IsDead() || !GetWorld()) return;

    SetHealth(Health - Damage);
    GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

    if (IsDead())
    {
        Killed(InstigatedBy);
        OnDeath.Broadcast();
    }
    else if (AutoHeal)
    {
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USEUHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
    }

    PlayCameraShakeEffect();
    ReportDamageEvent(Damage, InstigatedBy);
}

float USEUHealthComponent::GetPointDamageModifier(AActor* DamagedActor, const FName& BoneName)
{
    const auto Character = Cast<ACharacter>(DamagedActor);
    if (!Character) return 1.f;

    const auto PhysicalMaterial = Character->GetMesh()->GetBodyInstance(BoneName)->GetSimplePhysicalMaterial();
    if (!DamageMultipliers.Contains(PhysicalMaterial)) return 1.f;

    return DamageMultipliers[PhysicalMaterial];
}

void USEUHealthComponent::ReportDamageEvent(float Damage, AController* InstigatedBy)
{
    if (!InstigatedBy || !InstigatedBy->GetPawn() || !GetOwner())
        return;

    UAISense_Damage::ReportDamageEvent(GetWorld(),       //
            GetOwner(),                                  //
            InstigatedBy->GetPawn(),                     //
            Damage,                                      // 
            InstigatedBy->GetPawn()->GetActorLocation(), //
            GetOwner()->GetActorLocation());             //
}
