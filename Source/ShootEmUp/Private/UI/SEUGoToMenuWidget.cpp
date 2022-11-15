// Shoot Em Up. Educational Project

#include "UI/SEUGoToMenuWidget.h"
#include "Components/Button.h"
#include "SEUGameInstance.h"
#include "Kismet/GameplayStatics.h"

void USEUGoToMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if(MenuButton)
    {
        MenuButton->OnClicked.AddDynamic(this, &USEUGoToMenuWidget::OnGoToMenu);
    }
}

void USEUGoToMenuWidget::OnGoToMenu()
{
    if(!GetWorld()) return;

    const auto SEUGameInstance = GetWorld()->GetGameInstance<USEUGameInstance>();
    if(!SEUGameInstance) return;

    if(SEUGameInstance->GetMenuLevelName().IsNone()) return;
    
    UGameplayStatics::OpenLevel(this, SEUGameInstance->GetMenuLevelName());
}
