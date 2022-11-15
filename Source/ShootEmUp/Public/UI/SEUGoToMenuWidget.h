// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SEUGoToMenuWidget.generated.h"

class UButton;

UCLASS()
class SHOOTEMUP_API USEUGoToMenuWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* MenuButton;

    virtual void NativeOnInitialized() override;

private:
    UFUNCTION()
    void OnGoToMenu();
    
};
