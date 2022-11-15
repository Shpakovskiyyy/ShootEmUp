// Shoot Em Up. Educational Project

#include "Player/SEUBaseCharacter.h"
#include "Components/SEUCharacterMovementComponent.h"
#include "Components/SEUHealthComponent.h"
#include "GameFramework/Controller.h"
#include "Weapon/SEUWeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "Weapon/SEUBaseWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

ASEUBaseCharacter::ASEUBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<USEUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    PrimaryActorTick.bCanEverTick = true;
    
    HealthComponent = CreateDefaultSubobject<USEUHealthComponent>("SEUHealthComponent");
    WeaponComponent = CreateDefaultSubobject<USEUWeaponComponent>("WeaponComponent");
}

void ASEUBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(HealthComponent);
    check(GetCharacterMovement());
    check(GetMesh());

    OnHealthChanged(HealthComponent->GetHealth(), 0.f);
    HealthComponent->OnDeath.AddUObject(this, &ASEUBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ASEUBaseCharacter::OnHealthChanged);

    LandedDelegate.AddDynamic(this, &ASEUBaseCharacter::OnGroundLanded);
}

void ASEUBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ASEUBaseCharacter::TurnOff()
{
    WeaponComponent->StopShooting();
    WeaponComponent->Zoom(false);
    Super::TurnOff();
}

void ASEUBaseCharacter::Reset()
{
    WeaponComponent->StopShooting();
    WeaponComponent->Zoom(false);
    Super::Reset();
}

float ASEUBaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero()) return 0.0f;

    const auto VelocityNormal = GetVelocity().GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
    const auto Degrees = FMath::RadiansToDegrees(AngleBetween);

    return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}


void ASEUBaseCharacter::SetPlayerColor(const FLinearColor& NewColor)
{
    const auto MaterialInstance = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
    if(!MaterialInstance) return;
    
    MaterialInstance->SetVectorParameterValue(MaterialColorName, NewColor);
}

void ASEUBaseCharacter::OnDeath()
{
    //PlayAnimMontage(DeathAnimMontage);
    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(LifeSpanOnDeath);

    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    WeaponComponent->StopShooting();
    WeaponComponent->Zoom(false);

    GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
    GetMesh()->SetSimulatePhysics(true);

    UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
}

bool ASEUBaseCharacter::IsRunning() const
{
    return false;
}

void ASEUBaseCharacter::OnHealthChanged(float Health, float HealthDelta) 
{
}

void ASEUBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
    const auto FallVelocityZ = -GetVelocity().Z;

    if (FallVelocityZ < LandedDamageVelocity.X) return;

    const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
    TakeDamage(FinalDamage, FPointDamageEvent{}, nullptr, nullptr);
}