// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectHUD.h"
#include "SelectPlayer.h"
#include "SelectPlayerAnimInstance.h"
#include "SelectModeBase.h"
#include "SelectPawn.h"
#include "Kismet/GameplayStatics.h"
#include "../Global/ClientGameInstance.h"
#include "../DebugClass.h"
void USelectHUD::NativeConstruct()
{
	Super::NativeConstruct();
	//Button
	m_WukongButton = Cast<UButton>(GetWidgetFromName("WukongButton"));
	m_NoneButton = Cast<UButton>(GetWidgetFromName("NoneButton"));
	m_StartButton = Cast<UButton>(GetWidgetFromName("StartButton"));
	m_BackButton = Cast<UButton>(GetWidgetFromName("BackButton"));
	//Etc
	m_WukongText = Cast<UTextBlock>(GetWidgetFromName("WukongText"));
	m_NoneText = Cast<UTextBlock>(GetWidgetFromName("NoneText"));
	m_WukongBorder = Cast<UBorder>(GetWidgetFromName(TEXT("WukongBorder")));
	m_NoneBorder = Cast<UBorder>(GetWidgetFromName(TEXT("NoneBorder")));
	m_MainBorder = Cast<UBorder>(GetWidgetFromName(TEXT("Back")));
	//Panel
	m_SelectSubPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("SelectSubPanel")));
	m_DescSubPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("DescSubPannel")));
	//Custom
	m_WukongDesc = Cast<UUserWidget>(GetWidgetFromName(TEXT("UI_WukongDesc")));

	m_WukongButton->OnClicked.AddDynamic(this, &USelectHUD::WukongClick);
	m_NoneButton->OnClicked.AddDynamic(this, &USelectHUD::NoneClick);
	m_StartButton->OnClicked.AddDynamic(this, &USelectHUD::StartClick);
	m_BackButton->OnClicked.AddDynamic(this, &USelectHUD::BackClick);

}


void USelectHUD::WukongClick()
{
	//m_WukongDesc->SetVisibility(ESlateVisibility::Visible);
	//m_NoneBorder->SetVisibility(ESlateVisibility::Collapsed);
	//m_WukongBorder->SetVisibility(ESlateVisibility::Collapsed);
	//m_WukongText->SetVisibility(ESlateVisibility::Collapsed);
	//m_NoneText->SetVisibility(ESlateVisibility::Collapsed);
	//m_MainBorder->SetVisibility(ESlateVisibility::Collapsed);
	//m_StartButton->SetVisibility(ESlateVisibility::Visible);
	//m_BackButton->SetVisibility(ESlateVisibility::Visible);

	PlayAnimation(m_FadeAnim);
	//m_SelectSubPanel->SetVisibility(ESlateVisibility::Collapsed);
	//m_DescSubPanel->SetVisibility(ESlateVisibility::Visible);
	
	GetWorld()->GetTimerManager().SetTimer(m_PlayerAnimTimerHandle, this, &USelectHUD::ChangeAnim, 0.1f, false, 0.2f);

	//OpenLevel();

}
void USelectHUD::NoneClick()
{
	
}

void USelectHUD::StartClick()
{
	PlayAnimationReverse(m_FadeAnim);

	USelectPlayerAnimInstance* SelectAnim = Cast<USelectPlayerAnimInstance>(m_SelectPlayer->GetMesh()->GetAnimInstance());
	SelectAnim->ChangeAnimType(ESelectAnimType::Select);
	m_SelectSubPanel->SetVisibility(ESlateVisibility::Collapsed);
	
	GetOwningPlayerCameraManager()->StartCameraFade(0.0f, 1.f, 3.f, FLinearColor(0.f, 0.f, 0.f), true, true);
	
	OpenLevel();
}

void USelectHUD::OpenLevel()
{
	GetWorld()->GetTimerManager().SetTimer(m_LevelOpenTimerHandle, this, &USelectHUD::OpenPlayLevel, 3.1f, false, -1.f);
}

void USelectHUD::OpenPlayLevel()
{
	UGameplayStatics::OpenLevel(this, "PlayLevel");
}
void USelectHUD::ChangeAnim()
{
	if (m_SelectPlayer == nullptr)
	{
		FActorSpawnParameters	param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		m_SelectPlayer = GetWorld()->SpawnActor<ASelectPlayer>(m_Pawn,
			FVector(-10.0f, 190.f, 175.f), FRotator(0.f, 45.f, 0.f), param);

	}

	USelectPlayerAnimInstance* SelectAnim = Cast<USelectPlayerAnimInstance>(m_SelectPlayer->GetMesh()->GetAnimInstance());
	SelectAnim->ChangeAnimType(ESelectAnimType::Start);
	m_SelectPlayer->SetActorLocation(FVector(-10.f, 190.f, 175.f));
}

void USelectHUD::BackClick()
{
	PlayAnimationReverse(m_FadeAnim);

	/*m_SelectSubPanel->SetVisibility(ESlateVisibility::Visible);
	m_DescSubPanel->SetVisibility(ESlateVisibility::Collapsed);*/


	USelectPlayerAnimInstance* SelectAnim = Cast<USelectPlayerAnimInstance>(m_SelectPlayer->GetMesh()->GetAnimInstance());
	SelectAnim->ChangeAnimType(ESelectAnimType::Idle);

	m_SelectPlayer->SetActorLocation(FVector(1000.f, 0.f, 0.f));

}