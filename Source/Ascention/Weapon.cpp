// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "PlayerCharacter.h"

// Sets default values
AWeapon::AWeapon()
{
 	InitializeWeapon();

}
AWeapon::AWeapon(APlayerCharacter* playerCharacter){
	InitializeWeapon();

	BindWeapon(playerCharacter);
}

void AWeapon::InitializeWeapon(){
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	worldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WorldMesh"));
	RootComponent = worldMesh;

	worldMesh->SetSimulatePhysics(true);
	worldMesh->SetCollisionProfileName(TEXT("BlockAll"));

	firstPersonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FirstPersonMesh"));
	firstPersonMesh->SetSimulatePhysics(false);
	firstPersonMesh->SetCollisionProfileName(TEXT("NoCollision"));
	firstPersonMesh->SetVisibility(false);
	firstPersonMesh->AttachToComponent(this->worldMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	//Make 3rd person mesh be the same as the world mesh?
	thirdPersonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ThirdPersonMesh"));
	thirdPersonMesh->SetSimulatePhysics(false);
	thirdPersonMesh->SetCollisionProfileName(TEXT("NoCollision"));
	thirdPersonMesh->SetVisibility(false);
	thirdPersonMesh->AttachToComponent(this->worldMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	interactionRadius = 40.0f;

	interactionHitbox = CreateAbstractDefaultSubobject<USphereComponent>("CollectionSphere");
	interactionHitbox->AttachToComponent(this->worldMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	interactionHitbox->SetSphereRadius(interactionRadius, true);
	interactionHitbox->SetGenerateOverlapEvents(true);
	interactionHitbox->SetCollisionProfileName(TEXT("Pickup"));
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	

	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/**WEAPON FUNCTIONS**/
//Request a socket parameter in the future
void AWeapon::BindWeapon(APlayerCharacter* playerCharacter){
	if (playerCharacter == NULL)
		return;

	weaponOwner = playerCharacter;
	worldMesh->SetSimulatePhysics(false);
	//worldMesh->SetVisibility(false);
	//Ask for an initial socket to attach to
	this->AttachToActor(playerCharacter, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	//Set 1st and 3rd person meshes to be visible.

	this->interactionHitbox->SetCollisionProfileName(TEXT("NoCollision"));
	worldMesh->SetCollisionProfileName(TEXT("NoCollision"));
}
void AWeapon::UnbindWeapon(){
	
}

void AWeapon::FirePressed() {

}
void AWeapon::FireReleased() {

}

void AWeapon::AltFirePressed() {

}
void AWeapon::AltFireReleased() {

}

void AWeapon::AimPressed() {

}
void AWeapon::AimReleased() {

}

void AWeapon::ReloadPressed() {

}

void AWeapon::ReloadReleased() {

}

bool AWeapon::IsReloading(){
	return _reloading;
}
/**-----------------**/