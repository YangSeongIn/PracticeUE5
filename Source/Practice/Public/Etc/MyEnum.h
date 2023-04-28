// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyEnum.generated.h"

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	BareHandsMode UMETA(DisplayName = "BareHandsMode"),
	RifleMode UMETA(DisplayName = "RifleMode"),
	PistolMode UMETA(DisplayName = "PistolMode")
};
