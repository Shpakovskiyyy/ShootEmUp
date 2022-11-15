// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SEUGameDataWidget.generated.h"

class ASEUGameModeBase;
class ASEUPlayerState;

UCLASS()
class SHOOTEMUP_API USEUGameDataWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetCurrentRoundNum() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetTotalRoundNum() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetRoundTimeRemaining() const;

private:
    ASEUGameModeBase* GetSEUGameModeBase() const;
    ASEUPlayerState* GetSEUPlayerState() const;
    
};
