// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SEUPlayerState.generated.h"

UCLASS()
class SHOOTEMUP_API ASEUPlayerState : public APlayerState
{
	GENERATED_BODY()
    
public:
    int32 GetTeamID() const { return TeamID; }
    FLinearColor GetTeamColor() const { return TeamColor; }
    int32 GetKillCount() const { return KillCount; } 
    int32 GetDeathCount() const { return DeathCount; } 

    void SetTeamID(const int32 NewTeamID) { TeamID = NewTeamID; }
    void SetTeamColor(const FLinearColor& NewTeamColor) { TeamColor = NewTeamColor; }
    
    void AddKill() { ++KillCount; }
    void AddDeath() { ++DeathCount; }

    void LofInfo() const;

private:
    int32 TeamID;
    FLinearColor TeamColor;

    int32 KillCount = 0;
    int32 DeathCount = 0;
    
};
