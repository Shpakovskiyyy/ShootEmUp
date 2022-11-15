// Shoot Em Up. Educational Project

#include "UI/SEUPlayerStatsRowWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USEUPlayerStatsRowWidget::SetPlayerName(const FText& Name)
{
    if(!PlayerNameTextBlock) return;
    PlayerNameTextBlock->SetText(Name);
}

void USEUPlayerStatsRowWidget::SetKills(const FText& Kills)
{
    if(!KillsTextBlock) return;
    KillsTextBlock->SetText(Kills);
}

void USEUPlayerStatsRowWidget::SetDeaths(const FText& Deaths)
{
    if(!DeathsTextBlock) return;
    DeathsTextBlock->SetText(Deaths);
}

void USEUPlayerStatsRowWidget::SetTeam(const FText& Team)
{
    if(!TeamTextBlock) return;
    TeamTextBlock->SetText(Team);
}

void USEUPlayerStatsRowWidget::SetPlayerIndicatorVisibility(bool Visible)
{
    if(!PlayerIndicatorImage) return;
    PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void USEUPlayerStatsRowWidget::SetTeamColor(const FLinearColor& NewColor)
{
    if(!TeamImage) return;
    TeamImage->SetColorAndOpacity(NewColor);
}
