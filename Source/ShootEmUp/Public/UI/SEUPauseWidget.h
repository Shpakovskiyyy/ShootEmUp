// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "UI/SEUBaseWidget.h"
#include "Components/Button.h"
#include "SEUPauseWidget.generated.h"

class UButton;

UCLASS()
class SHOOTEMUP_API USEUPauseWidget : public USEUBaseWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* ClearPauseButton;

    virtual void NativeOnInitialized() override;

private:
    UFUNCTION()
    void OnClearPause();
    
};
