// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SelectPlayerAnimInstance.generated.h"

UENUM(BlueprintType)
enum class ESelectAnimType : uint8
{
	Start,
	Idle,
	Select
};

UCLASS()
class UNREALCLIENT_API USelectPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESelectAnimType m_AnimType;

public:

	void ChangeAnimType(ESelectAnimType Type)
	{
		m_AnimType = Type;
	}

	UFUNCTION()
		void AnimNotify_IdleStart();
};
