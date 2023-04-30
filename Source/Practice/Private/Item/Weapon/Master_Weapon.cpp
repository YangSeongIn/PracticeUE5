// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon/Master_Weapon.h"

// Sets default values
AMaster_Weapon::AMaster_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Ammo = 0;
	MaxAmmo = Ammo;
}

// Called when the game starts or when spawned
void AMaster_Weapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMaster_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

