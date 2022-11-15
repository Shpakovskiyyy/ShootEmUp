// Shoot Em Up. Educational Project

#include "UI/SEUSpectatorWidget.h"
#include "SEUUtils.h"
#include "Components/SEURespawnComponent.h"

bool USEUSpectatorWidget::GetRespawnTime(int32& OutCountDownTime) const
{
    const auto RespawnComponent = SEUUtils::GetSEUPlayerComponent<USEURespawnComponent>(GetOwningPlayer());
    if(!RespawnComponent || !RespawnComponent->IsRespawnInProgress()) return false;

    OutCountDownTime = RespawnComponent->GetRespawnTimeCountDown();
    return true;
}
