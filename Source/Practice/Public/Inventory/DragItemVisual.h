// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DragItemVisual.generated.h"

class UImage;
class UDataTable;

UCLASS()
class PRACTICE_API UDragItemVisual : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "Drag Item Visual", meta = (BindWidget))
		UImage* ItemIcon;
	FString ItemID;
	UPROPERTY(EditAnywhere)
		UDataTable* InventoryDataTable;

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	//virtual void NativeOnInitialized() override;
	//virtual FEventReply OnMouseButtonDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent) override;
	//virtual FEventReply OnPreviewMouseButtonDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent) override;
};
