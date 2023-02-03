// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "PlayerData.h"
#include "Weapon.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerCharacter::APlayerCharacter(){
	ConstructCharacter();

}

APlayerCharacter::APlayerCharacter(PlayerData* newOwningPlayer){
	ConstructCharacter();

	_owningPlayer = newOwningPlayer;
}

void APlayerCharacter::ConstructCharacter(){
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	
	_movementComponent = GetCharacterMovement();

	baseMovementSpeed = 600.0f;

	sprintSpeed = 1200.0f;
	_sprinting = false;

	initialJumpHeight = 500.0f;
	midAirJumpHeight = 500.0f;
	jumpQuantity = 2;

	dashSpeed = 6000.f;
	dashCooldown = 1.0f;
	_dashOnCD = false;

	
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay(){
	Super::BeginPlay();

	//IMPORTANT: ADD DYNAMICS ON BEGIN PLAY!!!
	OnActorBeginOverlap.AddDynamic(this, &APlayerCharacter::OnOverlap);

	if (GetWorld())
		playerCamera = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);

	//Init Movement
	_movementComponent->MaxWalkSpeed = baseMovementSpeed;

	_remainingJumps = jumpQuantity;

	// Display a debug message for five seconds. 
	// The -1 "Key" value argument prevents the message from being updated or refreshed.
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, "Player character initialized correctly.");
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}


void APlayerCharacter::SetOwner(PlayerData* newOwner){
	if(newOwner == NULL)
		return;

	_owningPlayer = newOwner;
}

PlayerData* APlayerCharacter::Owner(){
	if(_owningPlayer != NULL)
		return _owningPlayer;
	else
		return NULL;
}

void APlayerCharacter::InitializeCharacter(){

}

/**PLAYER INPUT**/
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	/**CHARACTER MOVEMENT**/
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::StopJump);

	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &APlayerCharacter::StartDash);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::StopSprint);

	//Replace this call to a call with a local function so the input can be customized
	PlayerInputComponent->BindAxis("LookHorizontal", this, &APlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookVertical", this, &APlayerCharacter::AddControllerPitchInput);
	/**-------------------**/

	/**EQUIPMENT CONTROL**/
	PlayerInputComponent->BindAction("Switch to weapon 1", IE_Pressed, this, &APlayerCharacter::SwitchToWeapon1);
	PlayerInputComponent->BindAction("Switch to weapon 2", IE_Pressed, this, &APlayerCharacter::SwitchToWeapon2);
	PlayerInputComponent->BindAction("Switch to heavy weapon", IE_Pressed, this, &APlayerCharacter::SwitchToHeavyWeapon);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::FirePressed);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APlayerCharacter::FireReleased);

	PlayerInputComponent->BindAction("AltFire", IE_Pressed, this, &APlayerCharacter::AltFirePressed);
	PlayerInputComponent->BindAction("AltFire", IE_Released, this, &APlayerCharacter::AltFireReleased);

	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &APlayerCharacter::AimPressed);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &APlayerCharacter::AimReleased);
	/**-----------------**/
}
/**---------**/

/**CHARACTER MOVEMENT**/
void APlayerCharacter::MoveForward(float value) {
	// Find out which way is "forward" and record that the player wants to move that way.
	FVector Direction = GetActorForwardVector();
	//Add in some speed calculations maybe.
	AddMovementInput(Direction, value);
}

void APlayerCharacter::MoveRight(float value) {
	// Find out which way is "right" and record that the player wants to move that way.
	FVector Direction = GetActorRightVector();
	//Add in some speed calculations maybe.
	AddMovementInput(Direction, value);
}

void APlayerCharacter::StartJump() {
	if (_remainingJumps <= 0)
		return;

	FVector _jumpVelocity = FVector(0,0,1.0f);

	if (_remainingJumps == jumpQuantity) {
		_jumpVelocity *= initialJumpHeight;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "Jumping from the ground.");
	}
	else {
		_jumpVelocity *= midAirJumpHeight;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "Jumping from mid air.");
	}

	_jumpVelocity.X += _movementComponent->Velocity.X;
	_jumpVelocity.Y += _movementComponent->Velocity.Y;

	--_remainingJumps;

	_movementComponent->Launch(_jumpVelocity);
}

void APlayerCharacter::StopJump() {

}

void APlayerCharacter::Landed(const FHitResult& Hit) {
	//Fires Twice, care
	Super::Landed(Hit);
	this->CharacterLand();
}

void APlayerCharacter::CharacterLand() {
	_remainingJumps = jumpQuantity;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "We landed, back to max jumps.");
}

void APlayerCharacter::StartDash() {
	if (_dashOnCD)
		return;
	if (_movementComponent->Velocity.IsNearlyZero())
		return;

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "Now dashing.");
	_dashOnCD = true;

	_movementComponent->MaxWalkSpeed = dashSpeed;
	FVector _dashScale = FVector(dashSpeed, dashSpeed, 0);
	_movementComponent->AddForce(_movementComponent->Velocity * _dashScale);

	GetWorldTimerManager().SetTimer(_dashCD, this, &APlayerCharacter::RefreshDash, dashCooldown, true);
	GetWorldTimerManager().SetTimer(_dashDuration, this, &APlayerCharacter::StopDash, 0.5f, true);
}

void APlayerCharacter::StopDash() {
	GetWorldTimerManager().ClearTimer(_dashDuration);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "Stopping dash.");
	_movementComponent->bForceMaxAccel = false;
	if(_sprinting)
		_movementComponent->MaxWalkSpeed = sprintSpeed;
	else
		_movementComponent->MaxWalkSpeed = baseMovementSpeed;
}

void APlayerCharacter::RefreshDash() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "Dash off cooldown.");
	GetWorldTimerManager().ClearTimer(_dashCD);
	_dashOnCD = false;
}

void APlayerCharacter::StartSprint() {
	_sprinting = true;
	_movementComponent->MaxWalkSpeed = sprintSpeed;
}

void APlayerCharacter::StopSprint() {
	_sprinting = false;
	_movementComponent->MaxWalkSpeed = baseMovementSpeed;
}
/**-----------------**/

/**WEAPON HANDLELING**/
//Rewrite this when the inventory system gets added
void APlayerCharacter::PickUpWeapon(AWeapon* weapon){
	if(weapon->weaponOwner != NULL)
		return;

	//Add logic to tell the weapon where to socket itself
	weapon->BindWeapon(this);

	//switch weapon type
	if(wieldedWeapon == NULL){
		weaponSlot1 = weapon;
		SwitchToWeapon1();
	}else{
		if(weaponSlot1 == NULL){
			weaponSlot1 = weapon;
		}else{
			if (weaponSlot2 == NULL){
				weaponSlot2 = weapon;
			}

		}
		
	}

}

void APlayerCharacter::SwitchToWeapon1(){
	if (weaponSlot1 == NULL)
		return;

	wieldedWeapon = weaponSlot1;
	FString output = "Switching wielded weapon to " + wieldedWeapon->displayName;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, output);
}
void APlayerCharacter::SwitchToWeapon2(){
	if (weaponSlot2 == NULL)
		return;

	wieldedWeapon = weaponSlot2;
	FString output = "Switching wielded weapon to " + wieldedWeapon->displayName;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, output);
}
void APlayerCharacter::SwitchToHeavyWeapon(){
	if (heavyWeaponSlot == NULL)
		return;

	wieldedWeapon = heavyWeaponSlot;
	FString output = "Switching wielded weapon to " + wieldedWeapon->displayName;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, output);
}

void APlayerCharacter::FirePressed(){
	if (wieldedWeapon == NULL)
		return;

	wieldedWeapon->FirePressed();
}
void APlayerCharacter::FireReleased(){
	if (wieldedWeapon == NULL)
		return;

	wieldedWeapon->FireReleased();
}

void APlayerCharacter::AltFirePressed(){

}
void APlayerCharacter::AltFireReleased(){

}

void APlayerCharacter::AimPressed(){

}
void APlayerCharacter::AimReleased(){

}

void APlayerCharacter::ReloadPressed(){

}
void APlayerCharacter::ReloadReleased(){

}


/**-----------------**/

/**MISCELANOUS**/
void APlayerCharacter::OnOverlap(class AActor* overlapedActor, class AActor* otherActor){
	if (!otherActor)
		return;

	UClass* otherClass = otherActor->GetClass();
	if (otherClass->IsChildOf(AWeapon::StaticClass())) {
		AWeapon* weapon = Cast<AWeapon>(otherActor);

		FString output = "Collided with " + weapon->displayName;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, output);

		PickUpWeapon(weapon);
	}
}
/**-----------**/