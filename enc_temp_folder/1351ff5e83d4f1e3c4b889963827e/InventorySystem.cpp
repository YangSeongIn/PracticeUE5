// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventorySystem.h"
#include "Engine/DataTable.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UInventorySystem::UInventorySystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Script/Engine.DataTable'/Game/Inventory/DT_ItemDataTable.DT_ItemDataTable'"));
	if (DataTable.Succeeded())
	{
		InventoryDataTable = DataTable.Object;
	}
}


// Called when the game starts
void UInventorySystem::BeginPlay()
{
	Super::BeginPlay();
	// ...
	for (int i = 0; i < inventorySize; i++) 
	{
		FInventorySlotStruct s{"None", 0};
		Contents.Add(s);
	}
}


// Called every frame
void UInventorySystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TTuple<bool, int> UInventorySystem::AddToInventory(FString ItemID, int Quantity)
{
	/*
	TTuple<int, bool> CurrentSlot = FindSlot(ItemID);
	if (CurrentSlot.Get<1>())
	{
		if (CurrentSlot.Get<0>() + Quantity > GetMaxStackSize(ItemID))
		{
			AddToStack(CurrentSlot.Get<0>(), GetMaxStackSize(ItemID) - );
		}
		else 
		{
			AddToStack(CurrentSlot.Get<0>(), Quantity);
		}
	}*/
	
	int QuantityRemaining = Quantity;
	bool bHasFailed = false;
	while (QuantityRemaining > 0 && !bHasFailed) {
		TTuple<int, bool> CurrentSlot = FindSlot(ItemID);
		if (CurrentSlot.Get<1>())
		{
			AddToStack(CurrentSlot.Get<0>(), 1);
			QuantityRemaining -= 1;
		}
		else 
		{
			if (AnyEmptySlotAvailable().Get<0>())
			{
				bool bIsSuccessToCreate = CreateNewStack(ItemID, 1);
				if (bIsSuccessToCreate)
				{
					QuantityRemaining -= 1;
				}
				else bHasFailed = true;
			}
			else bHasFailed = true;
		}
	}
	return MakeTuple(!bHasFailed, QuantityRemaining);
}

void UInventorySystem::RemoveFromInventory(FString ItemID, int Quantity)
{
	//Contents.Remove(Item);
}

TTuple<int, bool> UInventorySystem::FindSlot(FString ItemID)
{
	for (int i = 0; i < Contents.Num(); i++)
	{
		FInventorySlotStruct x = Contents[i];
		if (x.ItemID == ItemID)
		{
			if (x.Quantity < GetMaxStackSize(ItemID))
			{
				return MakeTuple(i, true);
			}
		}
	}
	return MakeTuple(-1, false);
}

int UInventorySystem::GetMaxStackSize(FString ItemID)
{
	TArray<FItemStruct*> ItemStructs;
	InventoryDataTable->GetAllRows<FItemStruct>(ItemID, ItemStructs);
	for (FItemStruct* ItemStruct : ItemStructs)
	{
		if (ItemStruct->ItemName == ItemID)
		{
			return ItemStruct->StackSize;
		}
	}
	return -1;
}

void UInventorySystem::AddToStack(int Idx, int Quantity)
{
	Contents[Idx].Quantity += Quantity;
}

TTuple<bool, int> UInventorySystem::AnyEmptySlotAvailable()
{
	for (int i = 0; i < Contents.Num(); i++)
	{
		if (Contents[i].Quantity == 0) return MakeTuple(true, i);
	}
	return MakeTuple(false, -1);
}

bool UInventorySystem::CreateNewStack(FString ItemID, int Quantity)
{
	if (AnyEmptySlotAvailable().Get<0>())
	{
		Contents[AnyEmptySlotAvailable().Get<1>()] = { ItemID, Quantity };
		return true;
	}
	else return false;
}

void UInventorySystem::DEBUGPrintContents()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("contents size : %d"), Contents.Num()));
	for (int i = 0; i < Contents.Num(); i++)
	{
		FInventorySlotStruct x = Contents[i];
		GEngine->AddOnScreenDebugMessage(
			-1,
			5,
			FColor::Blue,
			FString::Printf(TEXT("%d : %s, %d"), i, *x.ItemID, x.Quantity)
		);
	}
}

void UInventorySystem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UInventorySystem, Contents);
}

