// Fill out your copyright notice in the Description page of Project Settings.


#include "Pistol.h"


void APistol::FirePressed() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, "Pew!");
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

