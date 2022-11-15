// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SEUSpectatorWidget.generated.h"

UCLASS()
class SHOOTEMUP_API USEUSpectatorWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="UI")
    bool GetRespawnTime(int32& OutCountDownTime) const;
    
};
