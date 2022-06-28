// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientAnimInstance.h"
#include "../UnrealClient.h"

UMonsterAnimInstance::UMonsterAnimInstance()
	: Animations_(nullptr)
{

}

void UMonsterAnimInstance::NativeUpdateAnimation(float _DeltaTime)
{
	if (nullptr == Animations_)
	{
		return;
	}

	Super::NativeUpdateAnimation(_DeltaTime);

	if (false == (*Animations_).Contains(CurrentAnimationType_))
	{
		return;
	}

	UAnimMontage* FindAnimation = (*Animations_)[CurrentAnimationType_];

	if (nullptr == FindAnimation)
	{
		UE_LOG(ClientLog, Error, TEXT("%S(%u) > Animation Is Null"), __FUNCTION__, __LINE__);
	}


	if (true == Montage_IsPlaying(FindAnimation))
	{
		return;
	}

	if (0 != StartFunctions_.size())
	{

		for (auto& Function : StartFunctions_)
		{
			Function(CurrentAnimationType_);
		}
	}


	Montage_Play(FindAnimation);
}

void UMonsterAnimInstance::ChangeAnimation(ClientAnimationType _Type)
{
	if (CurrentAnimationType_ == _Type)
	{
		return;
	}

	CurrentAnimationType_ = _Type;
}

void UMonsterAnimInstance::AnimNotify_End()
{
	if (0 == EndFunctions_.size())
	{
		return;
	}

	for (auto& Function : EndFunctions_)
	{
		Function(CurrentAnimationType_);
	}

	// CurrentAnimationType_ = ClientAnimationType::Idle;
}

void UMonsterAnimInstance::AddEndFunctionBind(std::function<void(ClientAnimationType)> _BindFunction)
{
	EndFunctions_.push_back(_BindFunction);
}

void UMonsterAnimInstance::AddStartFunctionBind(std::function<void(ClientAnimationType)> _BindFunction)
{
	StartFunctions_.push_back(_BindFunction);
}