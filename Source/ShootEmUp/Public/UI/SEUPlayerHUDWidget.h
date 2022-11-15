// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "UI/SEUBaseWidget.h"
#include "SEUCoreTypes.h"
#include "Components/ProgressBar.h"
#include "SEUPlayerHUDWidget.generated.h"

class UProgressBar;

UCLASS()
class SHOOTEMUP_API USEUPlayerHUDWidget : public USEUBaseWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPercent() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerAlive() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerSpectating() const;

    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void OnTakeDamage();

    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetKillsCount() const;
    
    UFUNCTION(BlueprintCallable, Category = "UI")
    FString FormatBullets(int32 BulletsNum) const;

protected:
    UPROPERTY(meta = (BindWidget))
    UProgressBar* HealthBar;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float PercentColorThreshold = 0.3f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor DefaultColor = FLinearColor::White;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor CriticalHealthColor = FLinearColor::Red;
    
    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* DamageAnimation;
    
    virtual void NativeOnInitialized() override;

private:
    void OnHealthChanged(float Health, float HealthDelta);
    void OnNewPawn(APawn* NewPawn);
    void UpdateHealthBar();
    
};
