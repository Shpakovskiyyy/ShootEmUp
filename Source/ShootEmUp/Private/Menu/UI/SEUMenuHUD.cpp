// Shoot Em Up. Educational Project

#include "Menu/UI/SEUMenuHUD.h"
#include "UI/SEUBaseWidget.h"


void ASEUMenuHUD::BeginPlay()
{
    Super::BeginPlay();

    const auto MenuWidget = CreateWidget<USEUBaseWidget>(GetWorld(), MenuWidgetClass);
    if(MenuWidget)
    {
        MenuWidget->AddToViewport();
        MenuWidget->Show();
    }
}
