#pragma once

#include "Player/SEUPlayerState.h"

class APawn;

class SEUUtils
{
public:
    template <typename T>
    static T* GetSEUPlayerComponent(AActor* PlayerPawn)
    {
        if (!PlayerPawn) return nullptr;

        const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
        return Cast<T>(Component);
    }

    bool static AreEnemies(const AController* FirstController, const AController* SecondController)
    {
        if(!FirstController || !SecondController || FirstController == SecondController) return false;

        const auto FirstPlayerState = Cast<ASEUPlayerState>(FirstController->PlayerState);
        const auto SecondPlayerState = Cast<ASEUPlayerState>(SecondController->PlayerState);

        return FirstPlayerState && SecondPlayerState && FirstPlayerState->GetTeamID() != SecondPlayerState->GetTeamID();
    }
    
};