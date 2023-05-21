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
		UE_LOG(LogTemp, Log, TEXT("Drag ItemID : %s"), *ItemID);
		FItemStruct* ItemStruct = InventoryDataTable->FindRow<FItemStruct>(FName(ItemID), "");
		if (ItemStruct != nullptr)
		{
			GLog->Log("Drag ItemStruct oooo");
			ItemIcon->SetBrushFromTexture(ItemStruct->Thumbnail);
		}
		else
		{
			GLog->Log("Drag ItemStruct xxxx");
		}
	}
	else 
	{
		GLog->Log("Drag Item Visual Not Created!");
	}
}

void UDragItemVisual::NativeConstruct()
{
	Super::NativeConstruct();
	GLog->Log("Drag Construct");
}
