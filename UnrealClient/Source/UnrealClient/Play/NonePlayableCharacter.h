// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClientCharacter.h"
#include "NonePlayableCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCLIENT_API ANonePlayableCharacter : public AClientCharacter
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
public:
	ANonePlayableCharacter();

	FORCEINLINE class UMonsterAnimInstance* GetClientAnimInstance()
	{
		return m_AnimInst;
	}
	int ObjectIndex;
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClientData", meta = (AllowPrivateAccess = "true"))
		TMap <NonePlayerAnimationType, class UAnimMontage* > Animations_;

	class UMonsterAnimInstance* m_AnimInst;
};
