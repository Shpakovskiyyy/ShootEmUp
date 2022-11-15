// Shoot Em Up. Educational Project

#include "UI/SEUGameDataWidget.h"
#include "SEUGameModeBase.h"
#include "Player/SEUPlayerState.h"

int32 USEUGameDataWidget::GetCurrentRoundNum() const
{
    const auto GameMode = GetSEUGameModeBase();
    return GameMode ? GameMode->GetCurrenRoundNum() : 0;
}

int32 USEUGameDataWidget::GetTotalRoundNum() const
{
    const auto GameMode = GetSEUGameModeBase();
    return GameMode ? GameMode->GetGameData().RoundsNum : 0;
}

int32 USEUGameDataWidget::GetRoundTimeRemaining() const
{
    const auto GameMode = GetSEUGameModeBase();
    return GameMode ? GameMode->GetRoundTimeRemaining() : 0;
}

ASEUGameModeBase* USEUGameDataWidget::GetSEUGameModeBase() const
{
    return GetWorld() ? Cast<ASEUGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

ASEUPlayerState* USEUGameDataWidget::GetSEUPlayerState() const
{
    return GetOwningPlayer() ? Cast<ASEUPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
