// Shoot Em Up. Educational Project

#include "UI/SEUHealthBarWidget.h"
#include "Components/ProgressBar.h"

void USEUHealthBarWidget::SetHealthPercent(const float HealthPercent)
{
    if(!HealthBar) return;

    const auto HealthBarVisibility = (HealthPercent > PercentVisibilityThreshold || FMath::IsNearlyZero(HealthPercent)) //
                                        ? ESlateVisibility::Hidden
                                        : ESlateVisibility::Visible;
    HealthBar->SetVisibility(HealthBarVisibility);
    
    const auto HealthBarColor = HealthPercent > PercentColorThreshold ? DefaultColor : CriticalHealthColor;
    HealthBar->SetFillColorAndOpacity(HealthBarColor);

    HealthBar->SetPercent(HealthPercent);
}
