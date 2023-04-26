// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Master_Weapon.generated.h"

UCLASS()
class PRACTICE_API AMaster_Weapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMaster_Weapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(Editanywhere)
	UStaticMeshComponent* MainBody;

protected:
	UPROPERTY(Editanywhere)
	uint8 Ammo;
	uint8 MaxAmmo;

public:
	FORCEINLINE UStaticMeshComponent* GetMainBody() { return MainBody; };
	FORCEINLINE void SetMainBody(UStaticMeshComponent* mb) { MainBody = mb; };
	FORCEINLINE uint8 GetAmmo() { return Ammo; };
	FORCEINLINE void SetAmmo(uint8 n) { Ammo = n; };
};
