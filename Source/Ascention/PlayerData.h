// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class APlayerCharacter;

class ASCENTION_API PlayerData
{
public:

	PlayerData();
	~PlayerData();

private:

	//The character that represents this player
	APlayerCharacter* _playerCharacter;

public:
/********************************************************************************************************************
													FUNCTIONS
*********************************************************************************************************************/	
	//Binds a new player character to this player
	virtual void BindPlayerCharacter(APlayerCharacter* newPlayerCharacter);
	//Returns this player's character
	virtual APlayerCharacter* PlayerCharacter();
	



};

