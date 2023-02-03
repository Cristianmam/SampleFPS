// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Weapon.generated.h"

class APlayerCharacter;

UCLASS()
class ASCENTION_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	AWeapon(APlayerCharacter* playerCharacter);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	virtual void InitializeWeapon();



	bool _reloading;

public:	

/********************************************************************************************************************
													FUNCTIONS
*********************************************************************************************************************/	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Add a socket param to this, or make an overload and if no socket is provided just add weapon to inventory.
	UFUNCTION()
	void BindWeapon(APlayerCharacter* playerCharacter);
	UFUNCTION()
	void UnbindWeapon();

	UFUNCTION()
	virtual void FirePressed();
	UFUNCTION()
	virtual void FireReleased();

	UFUNCTION()
	virtual void AltFirePressed();
	UFUNCTION()
	virtual void AltFireReleased();

	UFUNCTION()
	virtual void AimPressed();
	UFUNCTION()
	virtual void AimReleased();

	UFUNCTION()
	virtual void ReloadPressed();
	UFUNCTION()
	virtual void ReloadReleased();
	UFUNCTION()
	virtual bool IsReloading();

	//Add in a switch socket function so the weapon may move around the player when swapped.

/********************************************************************************************************************
													VARIABLES
*********************************************************************************************************************/	

	//Weapon model while on the floor, not owned by anyone, might get replaced by a generic collectable object
	UPROPERTY(EditAnywhere,Category="Ascention|World|Visual",DisplayName="World mesh")
	UStaticMeshComponent* worldMesh;
	//Add a weapon model for 1st and 3rd person
	UPROPERTY(EditAnywhere, Category = "Ascention|World|Visual", DisplayName = "First person mesh")
	UStaticMeshComponent* firstPersonMesh;
	UPROPERTY(EditAnywhere, Category = "Ascention|World|Visual", DisplayName = "Third person mesh")
	UStaticMeshComponent* thirdPersonMesh;

	//The hitbox to collect or interact with the weapon
	UPROPERTY(EditAnywhere,Category="Ascention|World|Hitboxes",DisplayName="Interaction hitbox")
	USphereComponent* interactionHitbox;

	//The radious of the interaction hitbox
	UPROPERTY(EditAnywhere,Category="Ascention|World|Hitboxes",DisplayName="Interaction hitbox radious")
	float interactionRadius;

	//The CHARACTER that owns THE INSTANCE of this weapon, for player data use a reference to the class of the derived weapon
	UPROPERTY(VisibleAnywhere,Category="Ascention|Weapon Data",DisplayName="Owning character")
	APlayerCharacter* weaponOwner;

	/**WEAPON ATTRIBUTES**/
	//Should be a reference to a localization document, use a normal string for now
	UPROPERTY(EditAnywhere,Category="Ascention|Weapon Data|Attributes",DisplayName="Name path")
	FString displayName;

	//Add in a weight or slots taken

	//Does this weapon have an alt fire?
	UPROPERTY(EditAnywhere,Category="Ascention|Weapon Data|Attributes",DisplayName="Has altfire?")
	bool altFireEnabled;

	//Is this weapon ranged?
	UPROPERTY(EditAnywhere,Category="Ascention|Weapon Data|Attributes",DisplayName="Is ranged?")
	bool isRanged;

	//Can this weapon aim?
	UPROPERTY(EditAnywhere,Category="Ascention|Weapon Data|Attributes",DisplayName="Can use aim?")
	bool canAim;

	//Does this weapon need to reload? if not ammo should be taken straight from reserves as it fires
	UPROPERTY(EditAnywhere,Category="Ascention|Weapon Data|Attributes",DisplayName="Reloads?")
	bool reloads;

	UPROPERTY(EditAnywhere,Category="Ascention|Weapon Data|Attributes",DisplayName="Magazine size")
	int magazineSize;

	UPROPERTY(EditAnywhere,Category="Ascention|Weapon Data|Attributes",DisplayName="Reload time")
	float reloadTime;

	//Does the weapon keep firing while the fire button is held down?
	UPROPERTY(EditAnywhere,Category="Ascention|Weapon Data|Attributes",DisplayName="Has full auto?")
	bool fullAuto;

	//Delay between each shot the weapon takes, be it in full auto or semi mode. Basically rate of fire
	UPROPERTY(EditAnywhere,Category="Ascention|Weapon Data|Attributes",DisplayName="Delay between shots")
	float shotDelay;

	//Add a list with potential weapon modifiers, maybe a reference to an enum? look into it
	//Add a list with actual weapon modifiers
	/**-----------------**/
	



};
