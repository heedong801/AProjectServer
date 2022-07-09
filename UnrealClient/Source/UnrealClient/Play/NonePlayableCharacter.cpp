// Fill out your copyright notice in the Description page of Project Settings.


#include "NonePlayableCharacter.h"
#include "ClientAIController.h"

ANonePlayableCharacter::ANonePlayableCharacter() 
	: Super()
{
	AIControllerClass = AClientAIController::StaticClass();
}

void ANonePlayableCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_AnimInst = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	m_AnimInst->SetAnimationMap(&Animations_);
	m_AnimInst->ChangeAnimation(NonePlayerAnimationType::Idle);
}