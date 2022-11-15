// Shoot Em Up. Educational Project

#include "UI/SEUPauseWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"

void USEUPauseWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if(ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &USEUPauseWidget::OnClearPause);
    }
}

void USEUPauseWidget::OnClearPause()
{
    if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->ClearPause();
}
