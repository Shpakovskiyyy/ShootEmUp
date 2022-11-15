// Shoot Em Up. Educational Project

#include "Player/SEUPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogSEUPlayerState, All, All)

void ASEUPlayerState::LofInfo() const
{
    UE_LOG(LogSEUPlayerState, Display, TEXT("TeamID: %i, Kills: %i"), TeamID, KillCount);   
}
