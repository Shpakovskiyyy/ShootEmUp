// Shoot Em Up. Educational Project

#include "Menu/SEUMenuGameModeBase.h"
#include "Menu/SEUMenuPlayerController.h"
#include "Menu/UI/SEUMenuHUD.h"

ASEUMenuGameModeBase::ASEUMenuGameModeBase()
{
    PlayerControllerClass = ASEUMenuPlayerController::StaticClass();
    HUDClass = ASEUMenuHUD::StaticClass();
}
