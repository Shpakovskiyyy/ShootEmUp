// Shoot Em Up. Educational Project

#include "SEUGameModeBase.h"
#include "AIController.h"
#include "Player/SEUBaseCharacter.h"
#include "Player/SEUPlayerController.h"
#include "UI/SEUGameHUD.h"
#include "Player/SEUPlayerState.h"
#include "SEUUtils.h"
#include "Components/SEURespawnComponent.h"
#include "Weapon/SEUWeaponComponent.h"
#include "EngineUtils.h"

ASEUGameModeBase::ASEUGameModeBase()
{
    DefaultPawnClass = ASEUBaseCharacter::StaticClass();
    PlayerControllerClass = ASEUPlayerController::StaticClass();
    HUDClass = ASEUGameHUD::StaticClass();
    PlayerStateClass = ASEUPlayerState::StaticClass();
}

void ASEUGameModeBase::StartPlay()
{
    Super::StartPlay();

    SpawnAIControllers();
    CreateTeams();

    CurrentRound = 1;
    StartRound();

    SetMatchState(ESEUMatchState::InProgress);
}

UClass* ASEUGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if (InController && InController->IsA<AAIController>())
    {
        return AIPawnClass;
    }

    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ASEUGameModeBase::GotKilled(AController* Killer, AController* Victim)
{
    const auto KillerPlayerState = Killer ?  Cast<ASEUPlayerState>(Killer->PlayerState) : nullptr;
    const auto VictimPlayerState = Killer ?  Cast<ASEUPlayerState>(Victim->PlayerState) : nullptr;

    if(KillerPlayerState)
    {
        KillerPlayerState->AddKill();
    }
    if(VictimPlayerState)
    {
        VictimPlayerState->AddDeath();
    }

    StartRespawn(Victim);
}

void ASEUGameModeBase::RespawnRequest(AController* Controller)
{
    ResetOnePlayer(Controller);
}

bool ASEUGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
    const bool PauseSet = Super::SetPause(PC, CanUnpauseDelegate);
    if(PauseSet)
    {
        StopAllShooting();
        SetMatchState(ESEUMatchState::Paused);
    }

    return PauseSet;
}

bool ASEUGameModeBase::ClearPause()
{
    const auto PauseCleared =  Super::ClearPause();
    if(PauseCleared)
    {
        SetMatchState(ESEUMatchState::InProgress);
    }

    return PauseCleared;
}

void ASEUGameModeBase::SpawnAIControllers()
{
    if (!GetWorld()) return;

    for (int32 i = 0; i < GameData.PlayersNum - 1; ++i)
    {
        FActorSpawnParameters SpawnInfo;
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        const auto SEUAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
        RestartPlayer(SEUAIController);
    }
}

void ASEUGameModeBase::StartRound()
{
    RoundTimeRemaining = GameData.RoundTime;
    GetWorldTimerManager().SetTimer(RoundTimerHandle, this, &ASEUGameModeBase::RoundTimerUpdate, 1.f, true);
}

void ASEUGameModeBase::RoundTimerUpdate()
{
    if(--RoundTimeRemaining == 0)
    {
        GetWorldTimerManager().ClearTimer(RoundTimerHandle);
        
        if(CurrentRound + 1 <= GameData.RoundsNum)
        {
            ++CurrentRound;
            ResetPlayers();
            StartRound();
        }
        else
        {
            GameOver();
        }
    }
}

void ASEUGameModeBase::ResetPlayers()
{
    if(!GetWorld()) return;

    for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        ResetOnePlayer(It->Get());
    }
}

void ASEUGameModeBase::ResetOnePlayer(AController* Controller)
{
    if(Controller && Controller->GetPawn())
    {
        Controller->GetPawn()->Reset();
    }
    
    RestartPlayer(Controller);
    SetPlayerColor(Controller);
}

void ASEUGameModeBase::CreateTeams()
{
    if (!GetWorld()) return;

    int32 TeamID = 1;
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller) continue;

        const auto PlayerState = Cast<ASEUPlayerState>(Controller->PlayerState);
        if (!PlayerState) continue;

        PlayerState->SetTeamID(TeamID);
        PlayerState->SetTeamColor(GetTeamColorByTeamID(TeamID));
        PlayerState->SetPlayerName(Controller->IsPlayerController() ? "Player" : "Bot");
        SetPlayerColor(Controller);

        TeamID = TeamID == 1 ? 2 : 1;
    }
}

FLinearColor ASEUGameModeBase::GetTeamColorByTeamID(const int32 TeamID) const
{
    if(TeamID - 1 < GameData.TeamColors.Num())
    {
        return GameData.TeamColors[TeamID - 1];
    }

    return GameData.DefaultTeamColor;
}

void ASEUGameModeBase::SetPlayerColor(AController* Controller)
{
     if(!Controller) return;

    const auto Character = Cast<ASEUBaseCharacter>(Controller->GetPawn());
    if(!Character) return;

    const auto PlayerState = Cast<ASEUPlayerState>(Controller->PlayerState);
    if(!PlayerState) return;

    Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void ASEUGameModeBase::LogPlayerInfo() const
{
    if(!GetWorld()) return;
    
    for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if(!Controller) continue;

        const auto PlayerState = Cast<ASEUPlayerState>(Controller->PlayerState);
        if(!PlayerState) continue;

        //PlayerState->LofInfo();
    }
}

void ASEUGameModeBase::StartRespawn(AController* Controller)
{
    const bool RespawnAvailable = RoundTimeRemaining > GameData.MinRoundTimeRemainingToRespawn + GameData.RespawnTime;
    if(!RespawnAvailable) return;
    
    const auto RespawnComponent = SEUUtils::GetSEUPlayerComponent<USEURespawnComponent>(Controller);
    if(!RespawnComponent) return;

    RespawnComponent->Respawn(GameData.RespawnTime);
}

void ASEUGameModeBase::GameOver()
{
    LogPlayerInfo();

    for(auto Pawn : TActorRange<APawn>(GetWorld()))
    {
        if(Pawn)
        {
            Pawn->TurnOff();
            Pawn->DisableInput(nullptr);
        }
    }

    SetMatchState(ESEUMatchState::GameOver);
}

void ASEUGameModeBase::SetMatchState(ESEUMatchState NewState)
{
    if(MatchState == NewState) return;

    MatchState = NewState;
    OnMatchStateChanged.Broadcast(MatchState);
}

void ASEUGameModeBase::StopAllShooting()
{
    for(auto Pawn : TActorRange<APawn>(GetWorld()))
    {
        const auto WeaponComponent = SEUUtils::GetSEUPlayerComponent<USEUWeaponComponent>(Pawn);
        if(!WeaponComponent) return;

        WeaponComponent->StopShooting();
        WeaponComponent->Zoom(false);
    }
}
