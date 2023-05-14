// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory/InventoryItemStruct.h"
#include "InventorySystem.generated.h"

class UDataTable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UInventorySystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventorySystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	UDataTable* InventoryDataTable;

public:
	UPROPERTY(EditAnywhere)
	int inventorySize = 16;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	TArray<FInventorySlotStruct> Contents;

	TTuple<bool, int> AddToInventory(FString ItemID, int Quantity);
	void RemoveFromInventory(FString ItemID, int Quantity);
	TTuple<int, bool> FindSlot(FString ItemID);
	int GetMaxStackSize(FString ItemID);
	void AddToStack(int Idx, int Quantity);
	TTuple<bool, int> AnyEmptySlotAvailable();
	bool CreateNewStack(FString ItemID, int Quantity);
	UFUNCTION(BlueprintCallable)
		void DEBUGPrintContents();
	UFUNCTION(BlueprintCallable)
	TArray<FInventorySlotStruct> GetContents() { return Contents; };

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
