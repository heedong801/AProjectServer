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

	FORCEINLINE int32 GetCurrentCombo() { return m_CurrentCombo; }
	FORCEINLINE void SetCurrentCombo(int32 curCombo) { m_CurrentCombo = curCombo; }

	void SetTimeDillation();
	void SetTimeDefaultTimeDilation();

	void JumpKey();

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

	// 서버가 허락을 내렸냐?
	bool ServerPost;
	bool UDPReady;
	bool IsAttack;
	float AttTimeCheck;
	FTimerHandle TimeDillationHandle;

	bool m_Movable;
	bool m_IsSprint;

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

	class UClientAnimInstance* m_AnimInst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* m_AttackMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* m_SkyAttackMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<UAnimMontage*> m_AttackMontageArray;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<UAnimMontage*> m_SkyAttackMontageArray;
	// void TestPacketUpdate0();
};
