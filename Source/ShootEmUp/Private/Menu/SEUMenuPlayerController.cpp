// Shoot Em Up. Educational Project

#include "Menu/SEUMenuPlayerController.h"

void ASEUMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();

    SetInputMode(FInputModeUIOnly());
    bShowMouseCursor = true;
}
