// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DragItemVisual.generated.h"

class UBorder;
class UImage;
class UTextBlock;

UCLASS()
class PRACTICE_API UDragItemVisual : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "Drag Item Visual", meta = (BindWidget))
	UBorder* ItemBorder;

	UPROPERTY(BlueprintReadOnly, Category = "Drag Item Visual", meta = (BindWidget))
	UImage* ItemIcon;

	UPROPERTY(BlueprintReadOnly, Category = "Drag Item Visual", meta = (BindWidget))
	UTextBlock* AmmoQuantity;

	//virtual void NativeConstruct() override;
	//virtual void NativeOnInitialized() override;
	//virtual FEventReply OnMouseButtonDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent) override;
	//virtual FEventReply OnPreviewMouseButtonDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent) override;
};
