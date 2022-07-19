	// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClientCharacter.h"
#include "ClientEnums.h"
#include "ClientPlayCharacter.generated.h"

UCLASS()
class UNREALCLIENT_API AClientPlayCharacter : public AClientCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AClientPlayCharacter();

	FORCEINLINE class UClientAnimInstance* GetClientAnimInstance()
	{
		return m_AnimInst;
	}

	FORCEINLINE int32 GetCurrentCombo() const { return m_CurrentCombo; }
	FORCEINLINE void SetCurrentCombo(int32 curCombo) { m_CurrentCombo = curCombo; }
	FORCEINLINE void SetMoveable(bool bMoveable) { m_Movable = bMoveable; }
	FORCEINLINE bool GetMoveable() const { return m_Movable; }
	void SetTimeDillation();
	void SetTimeDefaultTimeDilation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void SendPlayerUpdatePacket();

	FVector MoveVector;
	FVector PrevVector;

	int32 m_MaxCombo;
	int32 m_CurrentCombo;
	int m_SkillIdx;
	int m_MoveStack;
	// 서버가 허락을 내렸냐?
	bool ServerPost;
	bool UDPReady;
	float AttTimeCheck;
	FTimerHandle TimeDillationHandle;

	bool m_Movable;
	bool m_IsSprint;
	bool m_IsInTown;

	void MoveForward(float _Rate);
	void MoveRight(float _Rate);

	void MoveStart();
	void MoveEnd();

	void Attack();

	void AnimationStart(ClientAnimationType _Value);
	void AnimationEnd(ClientAnimationType _Value);

	FVector MouseVectorToWorldVector();
	void SetChatTypeOne();
	void SetChatTypeInSec();
	void SetChatTypeAll();
	void Sprint();
	void StopSprint();
	void Skill1Key();
	void Skill2Key();
	void Skill3Key();
	void JumpKey();
	void InventoryKey();
	void EquipmentKey();

	bool SkillPlayAnim(int32 idx);

	class UClientAnimInstance* m_AnimInst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* m_AttackMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* m_SkyAttackMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<UAnimMontage*> m_AttackMontageArray;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<UAnimMontage*> m_SkyAttackMontageArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<UAnimMontage*> m_SkillMontageArray;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//	FPlayerInfo	m_PlayerInfo;
	// void TestPacketUpdate0();
};
