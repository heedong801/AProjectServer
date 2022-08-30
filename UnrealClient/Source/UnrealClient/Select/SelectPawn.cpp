// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectPawn.h"

// Sets default values
ASelectPawn::ASelectPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SetRootComponent(m_Camera);

	//m_Camera->SetRelativeLocation(FVector(0.f, 0.f, 100.f));

	//FPostProcessSettings CameraSetting = m_Camera->PostProcessSettings;
	//CameraSetting.VignetteIntensity = 1.0f;
	//CameraSetting.WhiteTemp = 7900.f;

	//PostProcessVolume-
}
