// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SEUCoreTypes.h"
#include "SEUGameModeBase.generated.h"

class AAIController;

UCLASS()
class SHOOTEMUP_API ASEUGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    ASEUGameModeBase();
    FOnMatchStateChangedSignature OnMatchStateChanged;

    virtual void StartPlay() override;
    
    virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

    void GotKilled(AController* Killer, AController* Victim);

    FGameData GetGameData() const { return GameData; }
    int32 GetCurrenRoundNum() const { return CurrentRound; }
    int32 GetRoundTimeRemaining() const { return RoundTimeRemaining; }

    void RespawnRequest(AController* Controller);

    virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
    virtual bool ClearPause() override;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<AAIController> AIControllerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<APawn> AIPawnClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FGameData GameData;

private:
    int32 CurrentRound = 1;
    int32 RoundTimeRemaining = 0;
    FTimerHandle RoundTimerHandle;
    ESEUMatchState MatchState = ESEUMatchState::WaitingForStart;

    void SpawnAIControllers();
    void StartRound();
    void RoundTimerUpdate();

    void ResetPlayers();
    void ResetOnePlayer(AController* Controller);

    void CreateTeams();
    FLinearColor GetTeamColorByTeamID(const int32 TeamID) const;
    void SetPlayerColor(AController* Controller);

    void LogPlayerInfo() const;

    void StartRespawn(AController* Controller);

    void GameOver();

    void SetMatchState(ESEUMatchState NewState);

    void StopAllShooting();
    
};
