// Shoot Em Up. Educational Project

#include "AI/SEUAICharacter.h"
#include "AI/SEUAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapon/SEUAIWeaponComponent.h"
#include "BrainComponent.h"
#include "Components/Widget.h"
#include "UI/SEUHealthBarWidget.h"
#include "Components/SEUHealthComponent.h"
#include "Components/WidgetComponent.h"

ASEUAICharacter::ASEUAICharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer.SetDefaultSubobjectClass<USEUAIWeaponComponent>("WeaponComponent"))
{
    AutoPossessAI = EAutoPossessAI::Disabled;
    AIControllerClass = ASEUAIController::StaticClass();

    bUseControllerRotationYaw = false;
    if(GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator { 0.f, 200.f, 0.f }; 
    }

    HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthBarWidgetComponent");
    HealthBarWidgetComponent->SetupAttachment(GetRootComponent());
    HealthBarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    HealthBarWidgetComponent->SetDrawAtDesiredSize(true);
}

void ASEUAICharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    
    UpdateHealthBarVisibility();
}

void ASEUAICharacter::BeginPlay()
{
    Super::BeginPlay();

    check(HealthBarWidgetComponent);
}

void ASEUAICharacter::OnDeath()
{
    Super::OnDeath();

    const auto SEUController = Cast<AAIController>(Controller);
    if(SEUController && SEUController->BrainComponent)
    {
        SEUController->BrainComponent->Cleanup();
    }
}

void ASEUAICharacter::OnHealthChanged(float Health, float HealthDelta)
{
    Super::OnHealthChanged(Health, HealthDelta);

    const auto HealthBarWidget = Cast<USEUHealthBarWidget>(HealthBarWidgetComponent->GetUserWidgetObject());
    if(!HealthBarWidget) return;

    HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent());
}

void ASEUAICharacter::UpdateHealthBarVisibility()
{
    if(!GetWorld() || !GetWorld()->GetFirstPlayerController() || !GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()) return;
    const auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
    
    const auto Distance = FVector::Distance(PlayerLocation, GetActorLocation());
    HealthBarWidgetComponent->SetVisibility(Distance < HealthBarRenderDistance, true);
}
