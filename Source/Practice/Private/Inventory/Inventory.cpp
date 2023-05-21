// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Inventory.h"
#include "Inventory/InventorySystem.h"
#include "Inventory/InventoryItemStruct.h"
#include "Inventory/InventoryItemSlot.h"
#include "Inventory/InventoryGrid.h"
#include "Components/WrapBox.h"
#include "PracticeCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "PracticeController.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UInventory::NativeConstruct()
{
	Super::NativeConstruct();
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(UGameplayStatics::GetPlayerController(this, 0), InventoryGrid);
	UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(true);
}

void UInventory::NativePreConstruct()
{
	Super::NativePreConstruct();

	APracticeCharacter* Character = Cast<APracticeCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (Character != nullptr)
	{
		InventoryGrid->DisplayInventory(Character->GetInventorySystem());
	}
}

void UInventory::NativeDestruct()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (IsValid(Controller))
	{
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(Controller);
		Controller->SetShowMouseCursor(false);
		APracticeCharacter* Character = Cast<APracticeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (Character != nullptr)
		{
			Character->SetInventoryWidgetNull();
		}
	}
	Super::NativeDestruct();
}

FReply UInventory::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::I)
	{
		RemoveFromParent();
	}
	return FReply::Handled();
}
