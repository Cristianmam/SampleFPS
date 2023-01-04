// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerCharacter.generated.h"

class PlayerData;
class AWeapon;

UCLASS()
class ASCENTION_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	// Constructor that sets the owner of this player character
	APlayerCharacter(PlayerData* newOwningPlayer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//Sets up general stull for the character
	virtual void ConstructCharacter();

	//The owner of this player character
	PlayerData* _owningPlayer;


	/**CHARACTER MOVEMENT**/
	UCharacterMovementComponent* _movementComponent;

	bool _sprinting;

	int _remainingJumps;

	bool _dashOnCD;
	FTimerHandle _dashCD;
	FTimerHandle _dashDuration;
	/**------------------**/

public:	
/********************************************************************************************************************
													FUNCTIONS
*********************************************************************************************************************/							
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Set the owning player player of this character
	virtual void SetOwner(PlayerData* newOwner);

	//Returns a pointer to the owner of this player character
	virtual PlayerData* Owner();

	//Initializes the character with all the data from the owning player
	virtual void InitializeCharacter();

	/**CHARACTER MOVEMENT**/
	virtual void MoveForward(float value);

	virtual void MoveRight(float value);

	virtual void StartJump();

	virtual void StopJump();

	virtual void Landed(const FHitResult& Hit) override;

	virtual void CharacterLand();

	virtual void StartDash();

	virtual void StopDash();

	virtual void RefreshDash();

	virtual void StartSprint();

	virtual void StopSprint();
	/**------------------**/

	/**WEAPON HANDLELING**/
	//Rewrite this when the inventory system gets added
	virtual void PickupWeapon(AWeapon* weapon);

	virtual void SwitchToWeapon1();
	virtual void SwitchToWeapon2();
	virtual void SwitchToHeavyWeapon();

	virtual void FirePressed();
	virtual void FireReleased();

	virtual void AltFirePressed();
	virtual void AltFireReleased();

	virtual void AimPressed();
	virtual void AimReleased();

	virtual void ReloadPressed();
	virtual void ReloadReleased();
	/**-----------------**/

	/**MISCELLANEOUS**/
	virtual void OnOverlap(class AActor* overlapedActor, class AActor* otherActor);
	/**-------------**/

/********************************************************************************************************************
													VARIABLES
*********************************************************************************************************************/	

	/**CHARACTER MOVEMENT**/
	UPROPERTY(EditAnywhere,Category="Character movement",DisplayName="Base movement speed");
	float baseMovementSpeed;

	UPROPERTY(EditAnywhere,Category="Character movement",DisplayName="Sprint speed");
	float sprintSpeed;

	UPROPERTY(EditAnywhere,Category="Character movement",DisplayName="Ground jump height");
	float initialJumpHeight;

	UPROPERTY(EditAnywhere,Category="Character movement",DisplayName="Double jump height");
	float midAirJumpHeight;

	//Get this from the player data in the future
	UPROPERTY(EditAnywhere,Category="Character movement",DisplayName="Number of jumps");
	int jumpQuantity;

	//Use player data for dash information
	UPROPERTY(EditAnywhere,Category="Character movement",DisplayName="Dash speed");
	float dashSpeed;

	UPROPERTY(EditAnywhere,Category="Character movement",DisplayName="Dash cooldown");
	float dashCooldown;
	/**-----------------**/

	/**EQUIPMENT**/
	UPROPERTY(VisibleAnywhere,Category="Equipment|Weapons",DisplayName="Wielded weapon")
	AWeapon* wieldedWeapon;

	UPROPERTY(VisibleAnywhere,Category="Equipment|Weapons",DisplayName="Weapon on slot 1")
	AWeapon* weaponSlot1;
	UPROPERTY(VisibleAnywhere,Category="Equipment|Weapons",DisplayName="Weapon on slot 2")
	AWeapon* weaponSlot2;
	UPROPERTY(VisibleAnywhere,Category="Equipment|Weapons",DisplayName="Weapon on heavy/utility slot")
	AWeapon* heavyWeaponSlot;
	/**---------**/

};
