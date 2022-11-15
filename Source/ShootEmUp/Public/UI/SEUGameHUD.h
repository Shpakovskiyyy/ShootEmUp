// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SEUCoreTypes.h"
#include "SEUGameHUD.generated.h"

class USEUBaseWidget;

UCLASS()
class SHOOTEMUP_API ASEUGameHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void DrawHUD() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PauseWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> GameOverWidgetClass;

    virtual void BeginPlay() override;

private:
    UPROPERTY()
    TMap<ESEUMatchState, USEUBaseWidget*> GameWidgets;

    UPROPERTY()
    USEUBaseWidget* CurrenWidget = nullptr;
    
    void OnMatchStateChanged(ESEUMatchState NewState);
    
};