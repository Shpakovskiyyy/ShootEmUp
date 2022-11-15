// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SEUCoreTypes.h"
#include "SEUGameInstance.generated.h"

class USoundClass;

UCLASS()
class SHOOTEMUP_API USEUGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
    FLevelData GetStartupLevel() const { return StartupLevel; } 
    void SetStartupLevelName(const FLevelData& NewLevel) { StartupLevel = NewLevel; }

    const TArray<FLevelData>& GetLevelsData() const { return LevelsData; }
    
    FName GetMenuLevelName() const { return MenuLevelName; }

    void ToggleVolume();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (ToolTip = "Level's name must be unique"))
    TArray<FLevelData> LevelsData;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName MenuLevelName = NAME_None;

    UPROPERTY(EditDefaultsOnly, Category = "Sound")
    USoundClass* MasterSoundClass;

private:
    FLevelData StartupLevel;
    
};
