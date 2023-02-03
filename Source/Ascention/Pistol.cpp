// Fill out your copyright notice in the Description page of Project Settings.


#include "Pistol.h"
#include "PlayerCharacter.h"
#include "DrawDebugHelpers.h"
#include "TargetDummy.h"


void APistol::FirePressed() {
	if (weaponOwner == NULL)
		return;

	//Check if in first person too?

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, "Pew!");
	//Do a raycast against an object of type "TargetDummy"
	//If we hit it call the target hit function

	FHitResult outHit;

	FVector origin = weaponOwner->playerCamera->GetCameraLocation();
	FVector forwardVector = weaponOwner->playerCamera->GetCameraRotation().Vector();

	origin = origin + (forwardVector * 3);
	FVector end = origin + (forwardVector * 5000);

	FCollisionQueryParams collisionParams;
	collisionParams.AddIgnoredActor(this->GetOwner());
	//Consider removing this to allow self shooting
	collisionParams.AddIgnoredActor(weaponOwner->GetOwner());

	//Remove this and the required reference when done
	DrawDebugLine(GetWorld(), origin, end, FColor::Green, false, 1, 0, 1);

	bool isHit = GetWorld()->LineTraceSingleByChannel(outHit, origin, end, ECC_Visibility, collisionParams);

	if (isHit) {
		AActor* hitActor = outHit.GetActor();

		//Replace this with a parent class/interface for enemies
		if (hitActor->GetClass()->IsChildOf(ATargetDummy::StaticClass())) {
			ATargetDummy* target = Cast<ATargetDummy>(hitActor);

			target->TargetHit();
		}
	}
}
void APistol::FireReleased() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, "Wep!");
}

void APistol::AltFirePressed() {

}

void APistol::AltFireReleased() {

}

void APistol::AimPressed() {

}

void APistol::AimReleased() {

}


void APistol::ReloadPressed() {

}

void APistol::ReloadReleased() {

}


bool APistol::IsReloading() {
	return false;
}

