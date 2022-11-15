// Shoot Em Up. Educational Project

#include "UI/SEUPlayerHUDWidget.h"
#include "Components/SEUHealthComponent.h"
#include "Weapon/SEUWeaponComponent.h"
#include "SEUUtils.h"
#include "Player/SEUPlayerState.h"

float USEUPlayerHUDWidget::GetHealthPercent() const
{
    const auto HealthComponent = SEUUtils::GetSEUPlayerComponent<USEUHealthComponent>(GetOwningPlayerPawn());
    if(!HealthComponent) return 0.f;

    return HealthComponent->GetHealthPercent();
}

bool USEUPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
    const auto WeaponComponent = SEUUtils::GetSEUPlayerComponent<USEUWeaponComponent>(GetOwningPlayerPawn());
    if(!WeaponComponent) return false;

    return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool USEUPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
    const auto WeaponComponent = SEUUtils::GetSEUPlayerComponent<USEUWeaponComponent>(GetOwningPlayerPawn());
    if(!WeaponComponent) return false;

    return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);
}

bool USEUPlayerHUDWidget::IsPlayerAlive() const
{
    const auto HealthComponent = SEUUtils::GetSEUPlayerComponent<USEUHealthComponent>(GetOwningPlayerPawn());
    return HealthComponent && !HealthComponent->IsDead();
}

bool USEUPlayerHUDWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;   
}

int32 USEUPlayerHUDWidget::GetKillsCount() const
{
    const auto Controller = GetOwningPlayer();
    if(!Controller) return 0;

    const auto PlayerState = Cast<ASEUPlayerState>(Controller->PlayerState);
    return PlayerState ? PlayerState->GetKillCount() : 0;
}

FString USEUPlayerHUDWidget::FormatBullets(int32 BulletsNum) const
{
    const int32 MaxLen = 3;
    const TCHAR PrefixSymbol = '0';

    auto BulletStr = FString::FromInt(BulletsNum);
    const auto SymbolsNumToAdd = MaxLen - BulletStr.Len();

    if (SymbolsNumToAdd > 0)
    {
        BulletStr = FString::ChrN(SymbolsNumToAdd, PrefixSymbol).Append(BulletStr);
    }

    return BulletStr;
}

void USEUPlayerHUDWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    if(GetOwningPlayer())
    {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USEUPlayerHUDWidget::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    }
}

void USEUPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
    if(HealthDelta < 0)
    {
        OnTakeDamage();

        if(!IsAnimationPlaying(DamageAnimation))
        {
            PlayAnimation(DamageAnimation);
        }
    }

    UpdateHealthBar();
}

void USEUPlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
    const auto HealthComponent = SEUUtils::GetSEUPlayerComponent<USEUHealthComponent>(NewPawn);
    if(HealthComponent && !HealthComponent->OnHealthChanged.IsBoundToObject(this)) 
    {
        HealthComponent->OnHealthChanged.AddUObject(this, &USEUPlayerHUDWidget::OnHealthChanged);
    }

    UpdateHealthBar();
}

void USEUPlayerHUDWidget::UpdateHealthBar()
{
    if(HealthBar)
    {
        HealthBar->SetFillColorAndOpacity(GetHealthPercent() > PercentColorThreshold ? DefaultColor : CriticalHealthColor);
    }
}

