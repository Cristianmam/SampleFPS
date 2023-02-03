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

