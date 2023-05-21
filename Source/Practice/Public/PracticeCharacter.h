// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Etc/MyEnum.h"

#include "PracticeCharacter.generated.h"

class UInventory;
class UInventorySystem;

UCLASS(config = Game)
class APracticeCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* InventoryAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* InteractAction;

public:
	APracticeCharacter();


protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void OpenInventory(const FInputActionValue& Value);
	void Interact();
	virtual void Jump() override;
	virtual void StopJumping() override;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> InventoryWidgetClass;
	UPROPERTY()
		UInventory* InventoryWidget;

	EPlayerState PlayerStateType;

	UPROPERTY(VisibleAnywhere)
		UInventorySystem* InventorySystem;

public:
	FORCEINLINE EPlayerState GetPlayerState() { return PlayerStateType; };
	FORCEINLINE void SetPlayerState(uint8 i) { PlayerStateType = EPlayerState(i); };
	FORCEINLINE UInventorySystem* GetInventorySystem() { return InventorySystem; };
	FORCEINLINE UInventory* GetInventoryWidget() { return InventoryWidget; };
	FORCEINLINE void SetInventoryWidgetNull() { InventoryWidget = nullptr; };

	void SwitchCurrentWeapon(int i);
};

