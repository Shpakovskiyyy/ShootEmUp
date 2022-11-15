// Shoot Em Up. Educational Project

#include "Components/SEURespawnComponent.h"
#include "SEUGameModeBase.h"

USEURespawnComponent::USEURespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USEURespawnComponent::Respawn(const int32 RespawnTime)
{
    if(!GetWorld()) return;

    RespawnTimeCountDown = RespawnTime;
    GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &USEURespawnComponent::RespawnTimerUpdate, 1.f, true);
}

bool USEURespawnComponent::IsRespawnInProgress() const
{
    return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle);
}

void USEURespawnComponent::RespawnTimerUpdate()
{
    if(--RespawnTimeCountDown == 0)
    {
        if(!GetWorld()) return;
        GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

        const auto GameMode = Cast<ASEUGameModeBase>(GetWorld()->GetAuthGameMode());
        if(!GameMode) return;

        GameMode->RespawnRequest(Cast<AController>(GetOwner()));
    }
}
