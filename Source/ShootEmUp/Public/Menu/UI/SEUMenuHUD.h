// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SEUMenuHUD.generated.h"

UCLASS()
class SHOOTEMUP_API ASEUMenuHUD : public AHUD
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> MenuWidgetClass;

    virtual void BeginPlay() override;
	
};
