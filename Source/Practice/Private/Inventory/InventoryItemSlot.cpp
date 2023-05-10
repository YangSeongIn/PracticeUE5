// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryItemSlot.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Inventory/DragItemVisual.h"
#include "Inventory/ItemDragDropOperation.h"
#include "Inventory/InventoryItemStruct.h"
#include "Engine/DataTable.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

UInventoryItemSlot::UInventoryItemSlot(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Script/Engine.DataTable'/Game/Inventory/DT_ItemDataTable.DT_ItemDataTable'"));
	if (DataTable.Succeeded())
	{
		InventoryDataTable = DataTable.Object;
	}

	//ItemID = "";
}

void UInventoryItemSlot::NativeConstruct()
{
	Super::NativeConstruct();

}

void UInventoryItemSlot::NativePreConstruct()
{
	Super::NativePreConstruct();

	TArray<FItemStruct*> ItemStructs;
	InventoryDataTable->GetAllRows<FItemStruct>(ItemID, ItemStructs);
	for (FItemStruct* ItemStruct : ItemStructs)
	{
		if (ItemStruct->ItemName == ItemID)
		{
			if (ItemIcon != nullptr)
			{
				ItemIcon->SetBrushFromTexture(ItemStruct->Thumbnail);
				ItemIcon->SetVisibility(ESlateVisibility::Visible);
				ItemQuantity->SetText(FText::FromString(FString::FromInt(Quantity)));
				ItemQuantity->SetVisibility(ESlateVisibility::Visible);
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("Icon Null 1"));
			}
			return;
		}
	}
	if (ItemIcon != nullptr)
	{
		ItemIcon->SetVisibility(ESlateVisibility::Hidden);
		ItemQuantity->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Icon Null 2"));
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
	if (InMouseEvent.IsMouseButtonDown("LeftMouseButton"))
	{
		//UWidgetBlueprintLibrary::DetectDragIfPressed();
	}
	return Reply;
}

void UInventoryItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	/*if (DragItemVisualClass != nullptr)
	{
		DragItemVisual = Cast<UDragItemVisual>(CreateWidget(this, DragItemVisualClass));
		if (DragItemVisual != nullptr && DragDropOperationClass)
		{
			DragDropOperation = Cast<UItemDragDropOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(DragDropOperationClass));
			if (DragDropOperation != nullptr)
			{

			}
		}
	}*/
}
