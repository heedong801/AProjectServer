// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectPlayerAnimInstance.h"


void USelectPlayerAnimInstance::AnimNotify_IdleStart()
{
	m_AnimType = ESelectAnimType::Idle;
}
