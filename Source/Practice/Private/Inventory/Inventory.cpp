// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Inventory.h"
#include "Inventory/InventorySystem.h"
#include "Inventory/InventoryItemStruct.h"
#include "Inventory/InventoryItemSlot.h"
#include "Inventory/InventoryGrid.h"
#include "Components/WrapBox.h"
#include "PracticeCharacter.h"
#include "Kismet/GameplayStatics.h"

void UInventory::NativePreConstruct()
{
	Super::NativePreConstruct();

	APracticeCharacter* Character = Cast<APracticeCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (Character != nullptr)
	{
		InventoryGrid->DisplayInventory(Character->GetInventorySystem());
	}
	
}
