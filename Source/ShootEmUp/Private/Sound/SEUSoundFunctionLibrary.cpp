// Shoot Em Up. Educational Project

#include "Sound/SEUSoundFunctionLibrary.h"
#include "Sound/SoundClass.h"

void USEUSoundFunctionLibrary::SetSoundClassVolume(USoundClass* SoundClass, const float DesiredVolume)
{
    if(!SoundClass) return;

    SoundClass->Properties.Volume = FMath::Clamp(DesiredVolume, 0.f, 1.f);
}

void USEUSoundFunctionLibrary::ToggleSoundClassVolume(USoundClass* SoundClass)
{
    if(!SoundClass) return;

    const auto NextVolume = SoundClass->Properties.Volume > 0.f ? 0.f : 1.f;
    SetSoundClassVolume(SoundClass, NextVolume);
}
