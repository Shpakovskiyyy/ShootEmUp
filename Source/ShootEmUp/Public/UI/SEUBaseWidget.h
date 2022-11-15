// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SEUBaseWidget.generated.h"

class USoundCue;

UCLASS()
class SHOOTEMUP_API USEUBaseWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void Show();

protected:
    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* ShowAnimation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* OpenSound;
    
};
