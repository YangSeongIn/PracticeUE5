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

	//UpdateInventory();
}

void UInventoryGrid::DisplayInventory(UInventorySystem* InventoryComp)
{
	this->InventorySystem = InventoryComp;
	ItemGrid->ClearChildren();
	UpdateInventory();
}

void UInventoryGrid::UpdateInventory()
{
	//APracticeCharacter* Character = Cast<APracticeCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	//if (Character != nullptr)
	//{
		//InventorySystem = Character->GetInventorySystem();
	if (IsValid(InventorySystem))
	{
		UInventoryItemSlot* ItemSlot = Cast<UInventoryItemSlot>(CreateWidget(GetWorld(), UInventoryItemSlot::StaticClass()));
		/*TArray<FInventorySlotStruct> Arr = InventorySystem->GetContents();
		for (FInventorySlotStruct x : Arr)
		{
			UInventoryItemSlot* ItemSlot = Cast<UInventoryItemSlot>(CreateWidget(GetWorld(), UInventoryItemSlot::StaticClass()));
			ItemSlot->ItemID = x.ItemID;
			ItemSlot->Quantity = x.Quantity;
			ItemGrid->AddChildToWrapBox(ItemSlot);
			GLog->Log("AddChild!");
		}*/
	}	
	//}
}
