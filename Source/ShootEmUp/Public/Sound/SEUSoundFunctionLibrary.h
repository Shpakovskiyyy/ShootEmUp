// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SEUSoundFunctionLibrary.generated.h"

class USoundClass;

UCLASS()
class SHOOTEMUP_API USEUSoundFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    static void SetSoundClassVolume(USoundClass* SoundClass, const float DesiredVolume);

    UFUNCTION(BlueprintCallable)
    static void ToggleSoundClassVolume(USoundClass* SoundClass);

};
