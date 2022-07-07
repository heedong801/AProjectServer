// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <functional>
#include <vector>
#include "Animation/AnimInstance.h"
#include "ClientEnums.h"
#include "MonsterAnimInstance.generated.h"

class UAnimMontage;
/**
 *
 */

UCLASS()
class UNREALCLIENT_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetAnimationMap(TMap <NonePlayerAnimationType, UAnimMontage* >* _Map)
	{
		Animations_ = _Map;
	}

	FORCEINLINE NonePlayerAnimationType GetAnimationType()
	{
		return CurrentAnimationType_;
	}

	void ChangeAnimation(NonePlayerAnimationType _Type);

	UMonsterAnimInstance();

	void AddEndFunctionBind(std::function<void(NonePlayerAnimationType)> _BindFunction);
	void AddStartFunctionBind(std::function<void(NonePlayerAnimationType)> _BindFunction);

protected:
	void NativeUpdateAnimation(float _DeltaTime);

	UFUNCTION()
		void AnimNotify_End();

private:
	NonePlayerAnimationType CurrentAnimationType_;

	TMap <NonePlayerAnimationType, UAnimMontage* >* Animations_;

	std::vector<std::function<void(NonePlayerAnimationType)>> EndFunctions_;
	std::vector<std::function<void(NonePlayerAnimationType)>> StartFunctions_;

};
