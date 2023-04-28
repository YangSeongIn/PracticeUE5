// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InventoryItemSlot.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Widget/DragItemVisual.h"

UInventoryItemSlot::UInventoryItemSlot(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UDragDropOperation> DragDropOperationAsset(TEXT("/Script/Engine.Blueprint'/Game/Widget/BP_DragDropOperation.BP_DragDropOperation'"));
	if (DragDropOperationAsset.Succeeded())
	{
		DragDropOperationClass = DragDropOperationAsset.Class;
	}
}

void UInventoryItemSlot::NativeConstruct()
{
	Super::NativeConstruct();
	
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
		UWidgetBlueprintLibrary::DetectDragIfPressed();
	}
	return Reply;
}

void UInventoryItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	if (DragItemVisualClass != nullptr)
	{
		DragItemVisual = Cast<UDragItemVisual>(CreateWidget(this, DragItemVisualClass));
		if (DragItemVisual != nullptr && DragDropOperationClass)
		{
			DragDropOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(DragDropOperationClass);
		}
	}
}
