// Shoot Em Up. Educational Project

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SEUWeaponComponent.h"
#include "SEUAIWeaponComponent.generated.h"

UCLASS()
class SHOOTEMUP_API USEUAIWeaponComponent : public USEUWeaponComponent
{
	GENERATED_BODY()

public:
	virtual void StartShooting() override;
	virtual void NextWeapon() override;

};
