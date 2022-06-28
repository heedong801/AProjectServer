// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugClass.h"

DEFINE_LOG_CATEGORY(AProject);
void PrintViewport(float Time, const FColor& Color, const FString& Text)
{
	GEngine->AddOnScreenDebugMessage(-1, Time, Color, Text);
}