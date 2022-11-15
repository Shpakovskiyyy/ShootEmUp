// Shoot Em Up. Educational Project

#include "Player/SEUPlayerController.h"
#include "Components/SEURespawnComponent.h"
#include "SEUGameModeBase.h"
#include "SEUCoreTypes.h"
#include "SEUGameInstance.h"

ASEUPlayerController::ASEUPlayerController()
{
    RespawnComponent = CreateDefaultSubobject<USEURespawnComponent>("RespawnComponent");
}

void ASEUPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if(GetWorld())
    {
        const auto GameMode = Cast<ASEUGameModeBase>(GetWorld()->GetAuthGameMode());
        if(GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &ASEUPlayerController::OnMatchStateChanged);
        }
    }
}

void ASEUPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    OnNewPawn.Broadcast(InPawn);
}

void ASEUPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    if(!InputComponent) return;

    InputComponent->BindAction("Pause", IE_Pressed, this, &ASEUPlayerController::OnPause);
    InputComponent->BindAction("Mute", IE_Pressed, this, &ASEUPlayerController::OnSoundMuted);
}

void ASEUPlayerController::OnPause()
{
    if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->SetPause(this);
}

void ASEUPlayerController::OnMatchStateChanged(ESEUMatchState NewState)
{
    if(NewState == ESEUMatchState::InProgress)
    {
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
    }
    else
    {
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
}

void ASEUPlayerController::OnSoundMuted()
{
    if(!GetWorld()) return;

    const auto SEUGameInstance = GetWorld()->GetGameInstance<USEUGameInstance>();
    if(!SEUGameInstance) return;

    SEUGameInstance->ToggleVolume();
}
