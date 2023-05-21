// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryGrid.h"
#include "Inventory/InventorySystem.h"
#include "Inventory/InventoryItemStruct.h"
#include "Inventory/InventoryItemSlot.h"
#include "Components/WrapBox.h"
#include "PracticeCharacter.h"
#include "Kismet/GameplayStatics.h"

void UInventoryGrid::NativePreConstruct()
{
	Super::NativePreConstruct();

	UpdateInventory();
}

void UInventoryGrid::DisplayInventory(UInventorySystem* InventoryComp)
{
	this->InventorySystem = InventoryComp;
	ItemGrid->ClearChildren();
	UpdateInventory();
}

void UInventoryGrid::UpdateInventory()
{
	APracticeCharacter* Character = Cast<APracticeCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (Character != nullptr)
	{
		InventorySystem = Character->GetInventorySystem();
		if (IsValid(InventorySystem))
		{
			//UInventoryItemSlot* ItemSlot = Cast<UInventoryItemSlot>(CreateWidget(GetWorld(), UInventoryItemSlot::StaticClass()));
			if (ItemSlotWidgetClass != nullptr)
			{
				GLog->Log("Slot Not Null In Grid");
				TArray<FInventorySlotStruct> Arr = InventorySystem->GetContents();
				for (FInventorySlotStruct x : Arr)
				{
					UInventoryItemSlot* ItemSlot = Cast<UInventoryItemSlot>(CreateWidget(this, ItemSlotWidgetClass));
					ItemSlot->ItemID = x.ItemID;
					ItemSlot->Quantity = x.Quantity;
					ItemSlot->InventorySystem = InventorySystem;
					ItemSlot->ContentIndex = ItemSlot->ContentIndex;
					ItemGrid->AddChildToWrapBox(ItemSlot);
					//ItemSlot->SetSlot();
				}
			}
			else
			{
				GLog->Log("Slot Null In Grid");
			}
		}	
	}
}
