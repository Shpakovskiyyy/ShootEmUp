// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "SEUCoreTypes.h"
#include "GameFramework/PlayerController.h"
#include "SEUPlayerController.generated.h"

class USEURespawnComponent;

UCLASS()
class SHOOTEMUP_API ASEUPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ASEUPlayerController();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USEURespawnComponent* RespawnComponent;

    virtual void BeginPlay() override;

    virtual void OnPossess(APawn* InPawn) override;

    virtual void SetupInputComponent() override;

private:
    void OnPause();
    void OnMatchStateChanged(ESEUMatchState NewState);
    void OnSoundMuted();
    
};
