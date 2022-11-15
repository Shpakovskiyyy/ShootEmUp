// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "SEUCoreTypes.h"
#include "UI/SEUBaseWidget.h"
#include "SEUGameOverWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class SHOOTEMUP_API USEUGameOverWidget : public USEUBaseWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UVerticalBox* PlayerStatsBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerStatsRowWidgetClass;

    UPROPERTY(meta = (BindWidget))
    UButton* RestartLevelButton;

    virtual void NativeOnInitialized() override;

private:
    void OnMatchStateChanged(ESEUMatchState NewState);
    void UpdatePlayersStats();

    UFUNCTION()
    void OnResetLevel();
    
};
