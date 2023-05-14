// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon/Item_Base.h"
#include "Item/ItemDataComponent.h"
#include "Engine/DataTable.h"
#include "Inventory/InventoryItemStruct.h"

// Sets default values
AItem_Base::AItem_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainBody"));
	SetRootComponent(MainBody);

	ItemDataComponent = CreateDefaultSubobject<UItemDataComponent>(TEXT("ItemDataComponent"));
}

// Called when the game starts or when spawned
void AItem_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FName AItem_Base::GetItemName()
{
	FDataTableRowHandle ItemData = ItemDataComponent->ItemID;
	FItemStruct* Item = ItemData.DataTable->FindRow<FItemStruct>(ItemData.RowName, "");

	return FName(Item->ItemName);
}

