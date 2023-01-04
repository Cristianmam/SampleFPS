// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerData.h"
#include "PlayerCharacter.h"

PlayerData::PlayerData()
{
}

PlayerData::~PlayerData()
{
}

//Binds a new player character to this player
void PlayerData::BindPlayerCharacter(APlayerCharacter* newPlayerCharacter){
    _playerCharacter = newPlayerCharacter;
}
//Returns this player's character
APlayerCharacter* PlayerData::PlayerCharacter(){
    if(_playerCharacter != NULL)
        return _playerCharacter;
    else
        return NULL;
}