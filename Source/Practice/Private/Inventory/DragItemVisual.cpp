// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/DragItemVisual.h"
#include "Inventory/InventoryItemStruct.h"
#include "Engine/DataTable.h"
#include "Components/Image.h"

void UDragItemVisual::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (InventoryDataTable != nullptr)
	{
		FItemStruct* ItemStruct = InventoryDataTable->FindRow<FItemStruct>(FName(ItemID), "");
		if (ItemStruct != nullptr)
		{
			ItemIcon->SetBrushFromTexture(ItemStruct->Thumbnail);
		}
	}
	GLog->Log("Drag Construct");
}

void UDragItemVisual::NativeConstruct()
{
	Super::NativeConstruct();
	
}
