// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <functional>
#include <vector>
#include "Animation/AnimInstance.h"
#include "ClientEnums.h"
#include "ClientAnimInstance.generated.h"

class UAnimMontage;
/**
 * 
 */

UCLASS()
class UNREALCLIENT_API UClientAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UClientAnimInstance();
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float m_Dir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float m_Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool m_CanAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool m_UseFullbody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool m_OnSky;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool m_DoubleJump;

	bool m_IsAttack;
	bool m_IsSkill;

	FTimerHandle m_AddGravityTimer;

	ClientAnimationType CurrentAnimationType_;

	// UFUNCTION	///////////////////////////////////////////////////////////////////
	UFUNCTION()
		void AnimNotify_AttackCombo();
	UFUNCTION()
		void AnimNotify_HitDamage();
	UFUNCTION()
		void AnimNotify_SlamEnd();
	UFUNCTION()
		void AnimNotify_AddGravity();
	UFUNCTION()
		void AnimNotify_AttackEnd();
	UFUNCTION()
		void AnimNotify_UseSkill();
	void AddGravity();
public:
	void SetDirection(float Dir) { m_Dir = Dir; }
	bool GetCanAttack() { return m_CanAttack; }
	void SetCanAttack(bool AttackEnable) { m_CanAttack = AttackEnable; }
	FName GetAttackMontageSectionName(int32 Section);

	void SetDoubleJump(bool jump) { m_DoubleJump = jump; }
	bool GetDoubleJump()	const { return m_DoubleJump; }

	void SetFullbody(float useFullbody);
	float GetFullbody() { return m_UseFullbody; }

	bool GetOnSky() { return m_OnSky; }

	void SetIsAttack(bool bAttack) { m_IsAttack = bAttack; }
	bool GetIsAttack() { return m_IsAttack; }
	FORCEINLINE ClientAnimationType GetAnimationType()
	{
		return CurrentAnimationType_;
	}
	
	void ChangeAnimation(ClientAnimationType _Type);
};
