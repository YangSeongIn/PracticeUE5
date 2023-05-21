// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "ItemDragDropOperation.generated.h"

class UInventorySystem;

UCLASS()
class PRACTICE_API UItemDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
	
private:
	int ContentIndex;
	UPROPERTY()
		UInventorySystem* InventoryComponent;

public:
	FORCEINLINE UInventorySystem* GetInventoryComponent() { return InventoryComponent; };
	FORCEINLINE void SetInventoryComponent(UInventorySystem* Inventory) { InventoryComponent = Inventory; };
	FORCEINLINE int GetContentIndex() { return ContentIndex; };
	FORCEINLINE void SetContentIndex(int Index) { ContentIndex = Index; };

};
