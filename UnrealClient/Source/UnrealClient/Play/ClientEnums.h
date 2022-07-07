// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ClientAnimationType : uint8 
{
	NONE UMETA(DisplayName = "애니메이션 지정 안됨"),
	Idle UMETA(DisplayName = "대기 애니메이션"),
	Move UMETA(DisplayName = "이동 애니메이션"),
	Attack1 UMETA(DisplayName = "공격 애니메이션"),
	Attack2 UMETA(DisplayName = "공격 애니메이션"),
	Attack3 UMETA(DisplayName = "공격 애니메이션"),
	Attack4 UMETA(DisplayName = "공격 애니메이션"),
	Death UMETA(DisplayName = "죽는 애니메이션"),
	Jump UMETA(DisplayName = "점프 애니메이션"),
	JumpAttack UMETA(DisplayName = "점프 공격 애니메이션"),
	DoubleJump UMETA(DisplayName = "더블 점프 애니메이션"),
	SlamAttack UMETA(DisplayName = "내려찍는 애니메이션"),

};

UENUM(BlueprintType)
enum class NonePlayerAnimationType : uint8
{
	NONE UMETA(DisplayName = "애니메이션 지정 안됨"),
	Idle UMETA(DisplayName = "대기 애니메이션"),
	Move UMETA(DisplayName = "이동 애니메이션"),
	Attack UMETA(DisplayName = "공격 애니메이션"),
	Death UMETA(DisplayName = "죽는 애니메이션"),

};