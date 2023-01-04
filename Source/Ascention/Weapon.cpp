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

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	staticMesh->AttachToComponent(this->RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	//StaticMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	staticMesh->SetSimulatePhysics(true);
	staticMesh->SetCollisionProfileName(TEXT("BlockAll"));

	interactionHitbox = CreateAbstractDefaultSubobject<USphereComponent>("Collection Sphere");
	interactionHitbox->AttachToComponent(this->RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	interactionHitbox->SetCollisionProfileName(TEXT("Pickup"));

	interactionRadius = 40.0f;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	

	interactionHitbox->SetSphereRadius(interactionRadius,true);
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/**WEAPON FUNCTIONS**/
void AWeapon::BindWeapon(APlayerCharacter* playerCharacter){

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

void AWeapon::ReloadWeapon() {

}

bool AWeapon::IsReloading(){
	return _reloading;
}
/**-----------------**/