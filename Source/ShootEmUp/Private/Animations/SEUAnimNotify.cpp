// Shoot Em Up. Educational Project

#include "Animations/SEUAnimNotify.h"

void USEUAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    OnNotified.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);
}
