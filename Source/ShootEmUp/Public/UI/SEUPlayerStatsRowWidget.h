// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SEUPlayerStatsRowWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class SHOOTEMUP_API USEUPlayerStatsRowWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetPlayerName(const FText& Name);
    void SetKills(const FText& Kills);
    void SetDeaths(const FText& Deaths);
    void SetTeam(const FText& Team);
    void SetPlayerIndicatorVisibility(bool Visible);
    void SetTeamColor(const FLinearColor& NewColor);

protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* PlayerNameTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* KillsTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* DeathsTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TeamTextBlock;

    UPROPERTY(meta = (BindWidget))
    UImage* PlayerIndicatorImage;

    UPROPERTY(meta = (BindWidget))
    UImage* TeamImage;
    
};
