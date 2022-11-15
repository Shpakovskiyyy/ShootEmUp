// Shoot Em Up. Educational Project

#include "SEUGameInstance.h"
#include "Sound/SEUSoundFunctionLibrary.h"

void USEUGameInstance::ToggleVolume()
{
    USEUSoundFunctionLibrary::ToggleSoundClassVolume(MasterSoundClass);
}
