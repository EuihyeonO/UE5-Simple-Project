// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerCharacter.h"

#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

//Content
#include "CCameraBoomData.h"

ACPlayerCharacter::ACPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	static ConstructorHelpers::FObjectFinder<UCCameraBoomData> CameraBoomDataRef(TEXT("/Script/ForStudying.CCameraBoomData'/Game/MyCharacter/Blueprint/DataAsset/DA_CameraBoomData.DA_CameraBoomData'"));
	if (CameraBoomDataRef.Object != nullptr)
	{
		CameraBoomData = CameraBoomDataRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> LookActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/MyCharacter/Blueprint/Input/InputAction/IA_LookAction.IA_LookAction'"));
	if (LookActionRef.Object != nullptr)
	{
		LookAction = LookActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/MyCharacter/Blueprint/Input/InputAction/IA_MoveAction.IA_MoveAction'"));
	if (MoveActionRef.Object != nullptr)
	{
		MoveAction = MoveActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> RunActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/MyCharacter/Blueprint/Input/InputAction/IA_RunACtion.IA_RunACtion'"));
	if (RunActionRef.Object != nullptr)
	{
		RunAction = RunActionRef.Object;
	}
}

void ACPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent != nullptr)
	{
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::LookActionFunc);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &ACPlayerCharacter::MoveStart);
		//EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::MoveActionFunc);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ACPlayerCharacter::MoveEnd);

		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &ACPlayerCharacter::RunStart);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &ACPlayerCharacter::RunEnd);
	}
}

void ACPlayerCharacter::MoveStart()
{
	UE_LOG(LogTemp, Log, TEXT("Move"));
	bIsMove = true;
}

void ACPlayerCharacter::MoveEnd()
{
	UE_LOG(LogTemp, Log, TEXT("MoveEnd"));
	bIsMove = false;
}

void ACPlayerCharacter::RunStart()
{
	UE_LOG(LogTemp, Log, TEXT("Run"));
	MoveInputSpeed = 2.0f;
}

void ACPlayerCharacter::RunEnd()
{
	UE_LOG(LogTemp, Log, TEXT("Walk"));
	MoveInputSpeed = 1.0f;
}

void ACPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	InputInit();
	CameraInit();
}

void ACPlayerCharacter::LookActionFunc(const FInputActionValue& _Value)
{
	FVector2D LookAxisVector = _Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void ACPlayerCharacter::MoveActionFunc(const FInputActionValue& _Value)
{
	FVector2D MoveAxisVector = _Value.Get<FVector2D>();

	const FRotator CharacterRotation = Controller->GetControlRotation();
	const FRotator YawRotation = FRotator(0.0f, CharacterRotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MoveAxisVector.X);
	AddMovementInput(RightDirection, MoveAxisVector.Y);

	if (MoveAxisVector.X >= 0)
	{
		MoveInputDIrection = MoveAxisVector.Y;
	}
	else
	{
		MoveInputDIrection = -MoveAxisVector.Y;
	}
}

void ACPlayerCharacter::Tick(float _DeltaSecond)
{
	Super::Tick(_DeltaSecond);
}

void ACPlayerCharacter::InputInit()
{
	if (InputMappingContext != nullptr)
	{
		APlayerController* PlayerController = CastChecked<APlayerController>(GetController());

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
}

void ACPlayerCharacter::CameraInit()
{
	if (CameraBoomData != nullptr)
	{
		FCameraBoomDataStruct DataStruct = CameraBoomData->GetData();

		CameraBoom->TargetArmLength = DataStruct.TargetArmLength;
		CameraBoom->bUsePawnControlRotation = DataStruct.bUsePawnControlRotation;
		CameraBoom->bDoCollisionTest = DataStruct.bDoCollisionTest;
		CameraBoom->bInheritRoll = DataStruct.bInheritRoll;
		CameraBoom->bInheritPitch = DataStruct.bInheritPitch;
		CameraBoom->bInheritYaw = DataStruct.bInheritYaw;

		CameraBoom->SetRelativeRotation(DataStruct.RelativeRotation);
	}
}



