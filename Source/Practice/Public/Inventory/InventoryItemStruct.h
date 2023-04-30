#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "InventoryItemStruct.generated.h"

class UInventoryItemSlot;
class UTexture2D;

USTRUCT(BlueprintType)
struct FInventorySlotStruct
{
public:
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		FString ItemID;
	UPROPERTY()
		int Quantity;
};

USTRUCT(BlueprintType)
struct FItemStruct : public FTableRowBase
{
public:
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ItemDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Thumbnail;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* ItemClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int StackSize;
};