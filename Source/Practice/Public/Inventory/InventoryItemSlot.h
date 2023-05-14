// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemSlot.generated.h"

class UBorder;
class UImage;
class UTextBlock;
//class UItemBase;
class UDragItemVisual;
class UItemDragDropOperation;
class UInventorySystem;
class UDataTable;

UCLASS()
class PRACTICE_API UInventoryItemSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// UInventoryItemSlot(const FObjectInitializer& ObjectInitializer);

public:
	/*UPROPERTY(BlueprintReadOnly, Category = "Drag Item Visual", meta = (BindWidget))
		UItemBase* ItemReference;*/
	UPROPERTY(BlueprintReadOnly, Category = "Drag Item Visual", meta = (BindWidget))
		UImage* ItemIcon;
	UPROPERTY(BlueprintReadOnly, Category = "Drag Item Visual", meta = (BindWidget))
		UTextBlock* ItemQuantity;

	UPROPERTY(BlueprintReadWrite, Category = "Drag Item Visual", meta = (ExposeOnSpawn = "true"))
		FString ItemID;
	UPROPERTY(BlueprintReadWrite, Category = "Drag Item Visual", meta = (ExposeOnSpawn = "true"))
		int Quantity;
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
		UInventorySystem* InventorySystem;

	UPROPERTY(EditAnywhere, Category = "Drag Item Visual")
		TSubclassOf<UUserWidget> DragItemVisualClass;
	UPROPERTY()
		UDragItemVisual* DragItemVisual;
	UPROPERTY(EditAnywhere)
		UDataTable* InventoryDataTable;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UDragDropOperation> DragDropOperationClass;
	UPROPERTY()
		UItemDragDropOperation* DragDropOperation;

protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual void NativeOnInitialized() override;
	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

public:
	void SetSlot();

};
