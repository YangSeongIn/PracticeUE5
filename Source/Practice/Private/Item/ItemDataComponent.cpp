// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemDataComponent.h"
#include "PracticeCharacter.h"
#include "Inventory/InventorySystem.h"

// Sets default values for this component's properties
UItemDataComponent::UItemDataComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UItemDataComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UItemDataComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UItemDataComponent::Interact(APracticeCharacter* Character)
{
	TTuple<bool, int> AddInVentoryTuple = Character->GetInventorySystem()->AddToInventory(ItemID.RowName.ToString(), Quantity);
	if (AddInVentoryTuple.Get<0>())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("Interact")));
		GetOwner()->Destroy();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("!!Interact")));
	}
}

