// Shoot Em Up. Educational Project

#include "Components/SEUCharacterMovementComponent.h"
#include "Player/SEUBaseCharacter.h"

float USEUCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();

    const ASEUBaseCharacter* Player = Cast<ASEUBaseCharacter>(GetPawnOwner());
    return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}
