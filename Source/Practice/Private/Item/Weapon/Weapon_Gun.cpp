// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon/Weapon_Gun.h"

void AWeapon_Gun::Reload()
{
	Ammo = MaxAmmo;
}

void AWeapon_Gun::Fire()
{
	if (Ammo == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, TEXT("Ammo Is 0"));
	}
	else
	{
		Ammo > 0 ? Ammo-- : Ammo = 0;
	}
}
