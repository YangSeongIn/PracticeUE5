// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Weapon/Master_Weapon.h"
#include "Weapon_Gun.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API AWeapon_Gun : public AMaster_Weapon
{
	GENERATED_BODY()
	
private:
	void Reload();

protected:
	virtual void Fire();

};
