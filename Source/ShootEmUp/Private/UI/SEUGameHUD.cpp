// Shoot Em Up. Educational Project

#include "UI/SEUGameHUD.h"
#include "Engine/Canvas.h"
#include "UI/SEUBaseWidget.h"
#include "SEUGameModeBase.h"

void ASEUGameHUD::DrawHUD()
{
    Super::DrawHUD();
}

void ASEUGameHUD::BeginPlay()
{
    Super::BeginPlay();

    GameWidgets.Add(ESEUMatchState::InProgress, CreateWidget<USEUBaseWidget>(GetWorld(), PlayerHUDWidgetClass));
    GameWidgets.Add(ESEUMatchState::Paused, CreateWidget<USEUBaseWidget>(GetWorld(), PauseWidgetClass));
    GameWidgets.Add(ESEUMatchState::GameOver, CreateWidget<USEUBaseWidget>(GetWorld(), GameOverWidgetClass));

    for(const auto WidgetPair : GameWidgets)
    {
        const auto GameWidget = WidgetPair.Value;
        if(!GameWidget) continue;

        GameWidget->AddToViewport();
        GameWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if(GetWorld())
    {
        const auto GameMode = Cast<ASEUGameModeBase>(GetWorld()->GetAuthGameMode());
        if(GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &ASEUGameHUD::OnMatchStateChanged);
        }
    }
}

void ASEUGameHUD::OnMatchStateChanged(ESEUMatchState NewState)
{
    if(CurrenWidget)
    {
        CurrenWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if(GameWidgets.Contains(NewState))
    {
        CurrenWidget = GameWidgets[NewState];
    }

    if(CurrenWidget)
    {
        CurrenWidget->SetVisibility(ESlateVisibility::Visible);
        CurrenWidget->Show();
    }
}