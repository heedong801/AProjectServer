// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectModeBase.h"
#include "SelectPlayerController.h"
#include "SelectPawn.h"

ASelectModeBase::ASelectModeBase()
{
	PlayerControllerClass = ASelectPlayerController::StaticClass();
	DefaultPawnClass = ASelectPawn::StaticClass();
	static ConstructorHelpers::FClassFinder<USelectHUD> SelectHUDClass(TEXT("WidgetBlueprint'/Game/UI/UI_SelectHUD.UI_SelectHUD_C'"));

	if (SelectHUDClass.Succeeded())
		m_SelectHUDClass = SelectHUDClass.Class;

	static ConstructorHelpers::FClassFinder<APawn> PawnClass(TEXT("Blueprint'/Game/Player/Select/BP_SelectPlayer.BP_SelectPlayer_C'"));
	if (PawnClass.Succeeded())
		m_Pawn = PawnClass.Class;

}

void ASelectModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}
void ASelectModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(m_SelectHUDClass))
	{
		m_SelectHUD = Cast<USelectHUD>(CreateWidget(GetWorld(), m_SelectHUDClass));

		if (m_SelectHUD)
		{
			m_SelectHUD->AddToViewport();
			m_SelectHUD->SetPawn(m_Pawn);
		}
	}

	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	//Controller->GetPawn()->SetHidden(true);
	FInputModeUIOnly Mode;
	//FInputModeGameOnly
	//FInputModeGameAndUI

	Controller->SetInputMode(Mode);
	Controller->bShowMouseCursor = true;
}

void ASelectModeBase::SpawnCharacter()
{

}
