// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CCameraBoomData.generated.h"

/**
 * 
 */
USTRUCT()
struct FCameraBoomDataStruct
{
	GENERATED_BODY()

	float TargetArmLength;
	FRotator RelativeRotation;
	uint8 bUsePawnControlRotation : 1;
	uint8 bInheritPitch : 1;
	uint8 bInheritYaw : 1;
	uint8 bInheritRoll : 1;
	uint8 bDoCollisionTest : 1;
};

UCLASS()
class FORSTUDYING_API UCCameraBoomData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	FCameraBoomDataStruct GetData()
	{
		FCameraBoomDataStruct ReturnStruct;

		ReturnStruct.TargetArmLength = TargetArmLength;
		ReturnStruct.RelativeRotation = RelativeRotation;
		ReturnStruct.bUsePawnControlRotation = bUsePawnControlRotation;
		ReturnStruct.bInheritPitch = bInheritPitch;
		ReturnStruct.bInheritYaw = bInheritYaw;
		ReturnStruct.bInheritRoll = bInheritRoll;
		ReturnStruct.bDoCollisionTest = bDoCollisionTest;

		return ReturnStruct;
	}

	UPROPERTY(EditAnywhere, Category = SpringArm)
	float TargetArmLength;

	UPROPERTY(EditAnywhere, Category = SpringArm)
	FRotator RelativeRotation;

	UPROPERTY(EditAnywhere, Category = SpringArm)
	uint32 bUsePawnControlRotation : 1;

	UPROPERTY(EditAnywhere, Category = SpringArm)
	uint32 bInheritPitch : 1;

	UPROPERTY(EditAnywhere, Category = SpringArm)
	uint32 bInheritYaw : 1;

	UPROPERTY(EditAnywhere, Category = SpringArm)
	uint32 bInheritRoll : 1;

	UPROPERTY(EditAnywhere, Category = SpringArm)
	uint32 bDoCollisionTest : 1;

};
