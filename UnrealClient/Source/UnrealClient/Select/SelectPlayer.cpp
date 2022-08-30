// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectPlayer.h"


// Sets default values
ASelectPlayer::ASelectPlayer()
{
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WukongMesh(TEXT("SkeletalMesh'/Game/ParagonSunWukong/Characters/Heroes/Wukong/Meshes/Wukong.Wukong'"));
	if (WukongMesh.Succeeded())
		GetMesh()->SetSkeletalMesh(WukongMesh.Object);
}



