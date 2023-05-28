// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryGrid.generated.h"

class UInventorySystem;
class UWrapBox;

UCLASS()
class PRACTICE_API UInventoryGrid : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;

public:
	UPROPERTY(BlueprintReadWrite)
		UInventorySystem* InventorySystem;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UWrapBox* ItemGrid;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> ItemSlotWidgetClass;

	UFUNCTION()
		void DisplayInventory(UInventorySystem* InventoryComp);
	UFUNCTION()
		void UpdateInventory();
	UFUNCTION()
		void UpdatedInventory();

};
