// Copyright Epic Games, Inc. All Rights Reserved.

#include "PracticeCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Inventory/InventorySystem.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Item/Weapon/Item_Base.h"
#include "Item/ItemDataComponent.h"
#include "Inventory//InventoryGrid.h"

#include "Inventory/Inventory.h"


//////////////////////////////////////////////////////////////////////////
// APracticeCharacter

APracticeCharacter::APracticeCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	InventorySystem = CreateDefaultSubobject<UInventorySystem>(TEXT("Inventory System"));
}

void APracticeCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	PlayerStateType = EPlayerState::BareHandsMode;
}

void APracticeCharacter::SwitchCurrentWeapon(int i)
{
}

//////////////////////////////////////////////////////////////////////////
// Input

void APracticeCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APracticeCharacter::Jump);
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APracticeCharacter::StopJumping);
		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APracticeCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APracticeCharacter::Look);
		
		//InventoryWidget
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Triggered, this, &APracticeCharacter::OpenInventory);

		//Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APracticeCharacter::Interact);
	}

}

void APracticeCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APracticeCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APracticeCharacter::OpenInventory(const FInputActionValue& Value)
{
	if (InventoryWidgetClass != nullptr)
	{
		if (InventoryWidget == nullptr)
		{
			InventoryWidget = Cast<UInventory>(CreateWidget(GetWorld(), InventoryWidgetClass));
			if (InventoryWidget != nullptr)
			{
				InventoryWidget->AddToViewport();
				InventoryWidget->InventoryGrid->DisplayInventory(InventorySystem);
			}
		}
		else
		{
			if (InventoryWidget->IsInViewport())
			{
				InventoryWidget->RemoveFromParent();
				InventoryWidget = nullptr;
			}
		}
	}
}

void APracticeCharacter::Interact()
{
	FVector StartLoc = GetActorLocation();
	FVector EndLoc = StartLoc + GetActorForwardVector() * 150;
	TArray<AActor*> ArrToIgnore;
	FHitResult OutHit;
	bool b = UKismetSystemLibrary::LineTraceSingle(this, StartLoc, EndLoc, ETraceTypeQuery::TraceTypeQuery1,
		false, ArrToIgnore, EDrawDebugTrace::Persistent, OutHit, true);
	if (b)
	{
		AItem_Base* Item = Cast<AItem_Base>(OutHit.GetActor());
		if (Item != nullptr)
		{
			Item->GetItemDataComponent()->Interact(this);
			Item->GetItemName();
		}
	}
}

void APracticeCharacter::Jump()
{
	Super::Jump();
	InventorySystem->DEBUGPrintContents();
}

void APracticeCharacter::StopJumping()
{
	Super::StopJumping();
}
