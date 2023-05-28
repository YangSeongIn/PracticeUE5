// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryItemSlot.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Inventory/DragItemVisual.h"
#include "Inventory/ItemDragDropOperation.h"
#include "Inventory/InventoryItemStruct.h"
#include "Engine/DataTable.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Inventory/InventorySystem.h"

//UInventoryItemSlot::UInventoryItemSlot(const FObjectInitializer& ObjectInitializer)
//	:Super(ObjectInitializer)
//{
//	//static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Script/Engine.DataTable'/Game/Inventory/DT_ItemDataTable.DT_ItemDataTable'"));
//	//if (DataTable.Succeeded())
//	//{
//	//	InventoryDataTable = DataTable.Object;
//	//}
//
//	//ItemID = "";
//}

void UInventoryItemSlot::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void UInventoryItemSlot::NativePreConstruct()
{
	Super::NativePreConstruct();

	//static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Script/Engine.DataTable'/Game/Inventory/DT_ItemDataTable.DT_ItemDataTable'"));
	//if (DataTable.Succeeded())
	//{
	//	InventoryDataTable = DataTable.Object;
	//}

	if (InventoryDataTable == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Inventory is null"));
	}
	else
	{ 
		//InventoryDataTable->GetAllRows<FItemStruct>(ItemID, ItemStructs);
		FItemStruct* ItemStruct = InventoryDataTable->FindRow<FItemStruct>(FName(ItemID), "");
		UE_LOG(LogTemp, Log, TEXT("ItemID : %s"), *ItemID);
		if (ItemStruct != nullptr)
		{
			if (ItemIcon != nullptr)
			{
				ItemIcon->SetBrushFromTexture(ItemStruct->Thumbnail);
				ItemIcon->SetVisibility(ESlateVisibility::Visible);
				GLog->Log("Item is in inventory");
			}
			else
			{
				GLog->Log("Icon Null 1");
			}
			UE_LOG(LogTemp, Log, TEXT("Quantity Text : %s"), *FString::FromInt(Quantity));
			ItemQuantity->SetText(FText::FromString(FString::FromInt(Quantity)));
			ItemQuantity->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			if (ItemIcon != nullptr)
			{
				ItemIcon->SetVisibility(ESlateVisibility::Hidden);
			}
			else
			{
				GLog->Log("Icon Null 2");
			}
			ItemQuantity->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UInventoryItemSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

FReply UInventoryItemSlot::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
	if (ItemID == "") return FReply::Unhandled();
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}
	return Reply;
}

void UInventoryItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	if (DragItemVisualClass != nullptr)
	{
		DragItemVisual = Cast<UDragItemVisual>(CreateWidget(this, DragItemVisualClass));
		if (DragItemVisual != nullptr)
		{
			DragItemVisual->ItemID = ItemID;
			DragDropOperation = Cast<UItemDragDropOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(UItemDragDropOperation::StaticClass()));
			if (DragDropOperation != nullptr)
			{
				DragDropOperation->SetInventoryComponent(InventorySystem);
				DragDropOperation->SetContentIndex(ContentIndex);
				DragDropOperation->DefaultDragVisual = DragItemVisual;
			}
		}
	}
	OutOperation = DragDropOperation;
}

bool UInventoryItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UItemDragDropOperation* DDO = Cast<UItemDragDropOperation>(InOperation);
	if (DDO != nullptr)
	{
		if (DDO->GetContentIndex() != ContentIndex || DDO->GetInventoryComponent() != InventorySystem)
		{
			GLog->Log("Drop success!");
			InventorySystem->ServerTransferSlots(DDO->GetContentIndex(), DDO->GetInventoryComponent(), ContentIndex);
		}
		else
		{
			GLog->Log("Drop fail!");
		}
	}
	else
	{
		GLog->Log("Drop null!");
	}
	return false;
}

void UInventoryItemSlot::SetSlot()
{
	if (InventoryDataTable == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Inventory is null"));
	}
	else
	{
		FItemStruct* ItemStruct = InventoryDataTable->FindRow<FItemStruct>(FName(ItemID), "");
		if (ItemStruct != nullptr)
		{
			if (ItemIcon != nullptr)
			{
				ItemIcon->SetBrushFromTexture(ItemStruct->Thumbnail);
				ItemIcon->SetVisibility(ESlateVisibility::Visible);
			}
			else
			{
				GLog->Log("Icon Null 1");
			}
			ItemQuantity->SetText(FText::FromString(FString::FromInt(Quantity)));
			ItemQuantity->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			if (ItemIcon != nullptr)
			{
				ItemIcon->SetVisibility(ESlateVisibility::Hidden);
			}
			else
			{
				GLog->Log("Icon Null 2");
			}
			ItemQuantity->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}