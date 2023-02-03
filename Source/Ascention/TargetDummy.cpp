// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetDummy.h"

// Sets default values
ATargetDummy::ATargetDummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	worldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WorldMesh"));
	RootComponent = worldMesh;
	worldMesh->SetSimulatePhysics(true);
	worldMesh->SetCollisionProfileName("PhysicsActor");

	worldMesh->SetEnableGravity(false);
}

// Called when the game starts or when spawned
void ATargetDummy::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATargetDummy::TargetHit() {
	Destroy();
}



