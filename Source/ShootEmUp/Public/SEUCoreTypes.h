#pragma once

#include "SEUCoreTypes.generated.h"

class ASEUBaseWeapon;
class UNiagaraSystem;
class USoundCue;

// Weapon delegate
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMagazineEmptySignature, ASEUBaseWeapon*)

// Health component delegates
DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, float);

USTRUCT(BlueprintType)
struct FAmmoData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    int32 BulletsCount;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "IsFinite"))
    int32 Magazines;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    bool IsFinite;
};

USTRUCT()
struct FWeaponData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TSubclassOf<ASEUBaseWeapon> WeaponClass;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    UAnimMontage* ReloadAnimMontage;
};

USTRUCT(BlueprintType)
struct FWeaponUIData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    UTexture2D* MainIcon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    UTexture2D* CrossHairIcon;
};


// VFX
USTRUCT(BlueprintType)
struct FDecalData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UMaterialInterface* Material;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FVector Size = FVector(10.f);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    float Lifetime = 10.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    float FadeoutTime = 0.7f;
};

USTRUCT(BlueprintType)
struct FImpactData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* NiagaraEffect;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FDecalData DecalData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    USoundCue* Sound;
    
};

USTRUCT(BlueprintType)
struct FGameData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "10"))
    int32 PlayersNum = 2;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "10"))
    int32 RoundsNum = 2;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "5", ClampMax = "300"))
    int32 RoundTime = 10; // in seconds

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    FLinearColor DefaultTeamColor = FLinearColor::Red;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    TArray<FLinearColor> TeamColors;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "20"))
    int32 RespawnTime = 5; // in seconds

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "10"))
    int32 MinRoundTimeRemainingToRespawn = 3;
    
};

UENUM(BlueprintType)
enum class ESEUMatchState : uint8
{
    WaitingForStart = 0,
    InProgress,
    Paused,
    GameOver
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature, ESEUMatchState);

USTRUCT(BlueprintType)
struct FLevelData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    FName LevelName = NAME_None;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    FName LevelDisplayName = NAME_None;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    UTexture2D* LevelThumbnail;
    
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnLevelSelectedSignature, const FLevelData&);

