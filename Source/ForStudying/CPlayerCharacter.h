// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "CPlayerCharacter.generated.h"

UENUM(BlueprintType)
enum class EPlayerState
{
	Idle UMETA(DisplayName = "Idle"),
	Move UMETA(DisplayName = "Move"),
	Sliding UMETA(DisplayName = "Sliding"),
};

UENUM(BlueprintType)
enum class EWeaponType
{
	Bared UMETA(DisplayName = "Bared"),
	Sword UMETA(DisplayName = "Sword"),
};

UCLASS()
class FORSTUDYING_API ACPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACPlayerCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveStart();
	void MoveEnd();

	void RunStart();
	void RunEnd();
	
	UFUNCTION(BlueprintCallable)
	void MoveActionFunc(const FInputActionValue& _Value);
	void LookActionFunc(const FInputActionValue& _Value);

	virtual void Tick(float _DeltaSecond) override;

protected:
	virtual void BeginPlay() override;

	//Input
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TObjectPtr<class UInputMappingContext> InputMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> RunAction;

	//DataAsset
protected:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TObjectPtr<class UCCameraBoomData> CameraBoomData;
	
	//Components
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UCameraComponent> FollowCamera;
	
	//value
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	uint8 bIsMove : 1 = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	float MoveInputSpeed = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	float MoveInputDIrection = 0.0f;

	//Action
private:

	//Init
private:
	void InputInit();
	void CameraInit();

};
