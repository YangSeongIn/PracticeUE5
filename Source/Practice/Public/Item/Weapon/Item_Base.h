// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item_Base.generated.h"

class UItemDataComponent;

UCLASS()
class PRACTICE_API AItem_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(Editanywhere)
	UStaticMeshComponent* MainBody;

	UPROPERTY(VisibleAnywhere)
	UItemDataComponent* ItemDataComponent;


public:
	FName GetItemName();

public:
	FORCEINLINE UStaticMeshComponent* GetMainBody() { return MainBody; };
	FORCEINLINE void SetMainBody(UStaticMeshComponent* mb) { MainBody = mb; };
	FORCEINLINE UItemDataComponent* GetItemDataComponent() { return ItemDataComponent; };

};
