// Shoot Em Up. Educational Project

#include "Menu/UI/SEUMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "SEUGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/HorizontalBox.h"
#include "Menu/UI/SEULevelItemWidget.h"
#include "Sound/SoundCue.h"

void USEUMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if(StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &USEUMenuWidget::OnStartGame);
    }
    
    if(QuitGameButton)
    {
        QuitGameButton->OnClicked.AddDynamic(this, &USEUMenuWidget::OnQuitGame);
    }
    
    InitLevelItems();
}

void USEUMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
    if(Animation != HideAnimation) return;
    
    const auto SEUGameInstance = GetSEUGameInstance();
    if(!SEUGameInstance) return;
    
    UGameplayStatics::OpenLevel(this, SEUGameInstance->GetStartupLevel().LevelName); 
    
}

void USEUMenuWidget::OnStartGame()
{
    PlayAnimation(HideAnimation);
    UGameplayStatics::PlaySound2D(GetWorld(), StartGameSound);
}

void USEUMenuWidget::OnQuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void USEUMenuWidget::InitLevelItems()
{
    const auto SEUGameInstance = GetSEUGameInstance();
    if(!SEUGameInstance) return;

    checkf(SEUGameInstance->GetLevelsData().Num() != 0, TEXT("Levels array must not be empty!"));

    if(!LevelItemsBox) return;
    LevelItemsBox->ClearChildren();

    for(auto LevelData : SEUGameInstance->GetLevelsData())
    {
        const auto LevelItemWidget = CreateWidget<USEULevelItemWidget>(GetWorld(), LevelItemWidgetClass);
        if(!LevelItemWidget) continue;

        LevelItemWidget->SetLevelData(LevelData);
        LevelItemWidget->OnLevelSelected.AddUObject(this, &USEUMenuWidget::OnLevelSelected);

        LevelItemsBox->AddChild(LevelItemWidget);
        LevelItemWidgets.Add(LevelItemWidget);
    }

    if(SEUGameInstance->GetStartupLevel().LevelName.IsNone())
    {
        OnLevelSelected(SEUGameInstance->GetLevelsData()[0]);
    }
    else
    {
        OnLevelSelected(SEUGameInstance->GetStartupLevel());
    }
}

void USEUMenuWidget::OnLevelSelected(const FLevelData& LevelData)
{
    const auto SEUGameInstance = GetSEUGameInstance();
    if(!SEUGameInstance) return;

    SEUGameInstance->SetStartupLevelName(LevelData);

    for(auto LevelItemWidget : LevelItemWidgets)
    {
        if(LevelItemWidget)
        {
            const auto IsSelected = LevelData.LevelName == LevelItemWidget->GetLevelData().LevelName;
            LevelItemWidget->SetSelected(IsSelected);
        }
    }
}

USEUGameInstance* USEUMenuWidget::GetSEUGameInstance() const
{
    if(!GetWorld()) return nullptr;

    return GetWorld()->GetGameInstance<USEUGameInstance>();
}
