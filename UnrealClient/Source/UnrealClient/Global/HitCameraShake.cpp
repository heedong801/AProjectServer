// Fill out your copyright notice in the Description page of Project Settings.


#include "HitCameraShake.h"

UHitCameraShake::UHitCameraShake()
{
	OscillationDuration = 0.2f;

	OscillationBlendInTime = 0.1f;
	OscillationBlendOutTime = 0.1f;

	LocOscillation.Y.Amplitude = 25.f;
	LocOscillation.Y.Frequency = 70.f;
	LocOscillation.Y.InitialOffset = EInitialOscillatorOffset::EOO_OffsetZero;
	//
	LocOscillation.Z.Amplitude = 10.f;
	LocOscillation.Z.Frequency = 80.f;
	LocOscillation.Z.InitialOffset = EInitialOscillatorOffset::EOO_OffsetZero;
	//
	//LocOscillation.X.Amplitude = 25.f;
	//LocOscillation.X.Frequency = 30.f;
	//LocOscillation.X.InitialOffset = EInitialOscillatorOffset::EOO_OffsetZero;

	bSingleInstance = true;

}