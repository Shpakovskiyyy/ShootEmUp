// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SEUHealthBarWidget.generated.h"

class UProgressBar;

UCLASS()
class SHOOTEMUP_API USEUHealthBarWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetHealthPercent(const float HealthPercent);

protected:
    UPROPERTY(meta = (BindWidget))
    UProgressBar* HealthBar;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float PercentVisibilityThreshold = 0.8f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float PercentColorThreshold = 0.3f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor DefaultColor = FLinearColor::White;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor CriticalHealthColor = FLinearColor::Red;
    
};
