// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "UI/SEUBaseWidget.h"
#include "SEUCoreTypes.h"
#include "SEUMenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class USEUGameInstance;
class USEULevelItemWidget;
class USoundCue;

UCLASS()
class SHOOTEMUP_API USEUMenuWidget : public USEUBaseWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* StartGameButton;

    UPROPERTY(meta = (BindWidget))
    UButton* QuitGameButton;

    UPROPERTY(meta = (BindWidget))
    UHorizontalBox* LevelItemsBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> LevelItemWidgetClass;

    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* HideAnimation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* StartGameSound;
    
    virtual void NativeOnInitialized() override;
    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

private:
    UPROPERTY()
    TArray<USEULevelItemWidget*> LevelItemWidgets;
    
    UFUNCTION()
    void OnStartGame();

    UFUNCTION()
    void OnQuitGame();

    void InitLevelItems();
    void OnLevelSelected(const FLevelData& LevelData);
    USEUGameInstance* GetSEUGameInstance() const;
    
};
