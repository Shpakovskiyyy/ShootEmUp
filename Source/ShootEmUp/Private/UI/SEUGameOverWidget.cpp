// Shoot Em Up. Educational Project

#include "UI/SEUGameOverWidget.h"
#include "SEUGameModeBase.h"
#include "Player/SEUPlayerState.h"
#include "UI/SEUPlayerStatsRowWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void USEUGameOverWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    if(GetWorld())
    {
        const auto GameMode = Cast<ASEUGameModeBase>(GetWorld()->GetAuthGameMode());
        if(GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &USEUGameOverWidget::OnMatchStateChanged);
        }
    }

    if(RestartLevelButton)
    {
        RestartLevelButton->OnClicked.AddDynamic(this, &USEUGameOverWidget::OnResetLevel);
    }
}

void USEUGameOverWidget::OnMatchStateChanged(ESEUMatchState NewState)
{
    if(NewState == ESEUMatchState::GameOver)
    {
        UpdatePlayersStats();
    }
}

void USEUGameOverWidget::UpdatePlayersStats()
{
    if(!GetWorld() || !PlayerStatsBox) return;

    // Just to be sure that VerticalBox is clear before adding any stats
    PlayerStatsBox->ClearChildren();

    for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if(!Controller) continue;

        const auto PlayerState = Cast<ASEUPlayerState>(Controller->PlayerState);
        if(!PlayerState) continue;

        const auto PlayerStatsRowWidget = CreateWidget<USEUPlayerStatsRowWidget>(GetWorld(), PlayerStatsRowWidgetClass);
        if(!PlayerStatsRowWidget) continue;

        PlayerStatsRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
        PlayerStatsRowWidget->SetKills(FText::FromString(FString::FromInt(PlayerState->GetKillCount())));
        PlayerStatsRowWidget->SetDeaths(FText::FromString(FString::FromInt(PlayerState->GetDeathCount())));
        PlayerStatsRowWidget->SetTeam(FText::FromString(FString::FromInt(PlayerState->GetTeamID())));
        PlayerStatsRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());
        PlayerStatsRowWidget->SetTeamColor(PlayerState->GetTeamColor());
        
        PlayerStatsBox->AddChild(PlayerStatsRowWidget);
    }
}

void USEUGameOverWidget::OnResetLevel()
{
    const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
    UGameplayStatics::OpenLevel(GetWorld(), FName(CurrentLevelName));
}
