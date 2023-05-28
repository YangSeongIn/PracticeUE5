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
				TArray<FInventorySlotStruct> Arr = InventorySystem->GetContents();
				for (int i = 0; i < Arr.Num(); i++)
				{
					UInventoryItemSlot* ItemSlot = Cast<UInventoryItemSlot>(CreateWidget(this, ItemSlotWidgetClass));
					ItemSlot->ItemID = Arr[i].ItemID;
					ItemSlot->Quantity = Arr[i].Quantity;
					ItemSlot->InventorySystem = InventorySystem;
					ItemSlot->ContentIndex = i;
					ItemGrid->AddChildToWrapBox(ItemSlot);
				}
				InventorySystem->OnInventoryUpdate.AddUFunction(this, FName("UpdatedInventory"));
			}
		}	
	}
}

void UInventoryGrid::UpdatedInventory()
{
	ItemGrid->ClearChildren();
	UpdateInventory();
}
