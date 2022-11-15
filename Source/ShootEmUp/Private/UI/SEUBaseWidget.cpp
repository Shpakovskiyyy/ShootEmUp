// Shoot Em Up. Educational Project

#include "UI/SEUBaseWidget.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

void USEUBaseWidget::Show()
{
    PlayAnimation(ShowAnimation);
    UGameplayStatics::PlaySound2D(GetWorld(), OpenSound);
}
