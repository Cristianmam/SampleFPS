#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Pistol.generated.h"

/**
 * 
 */
UCLASS()
class ASCENTION_API APistol : public AWeapon
{
	GENERATED_BODY()

public:

	//In this class we define all common things to pistols of different types, should a pistol need a specific variation
	//say, a different fire mode, it can be overriden on the inheriting class/blueprint.
	virtual void FirePressed() override;

	virtual void FireReleased() override;


	virtual void AltFirePressed() override;

	virtual void AltFireReleased() override;


	virtual void AimPressed() override;

	virtual void AimReleased() override;


	virtual void ReloadPressed() override;

	virtual void ReloadReleased() override;

	virtual bool IsReloading() override;
	
};

