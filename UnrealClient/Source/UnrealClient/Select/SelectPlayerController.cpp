// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectPlayerController.h"
#include "SelectPlayer.h"

ASelectPlayerController::ASelectPlayerController()
{
	PrimaryActorTick.bCanEverTick = false;

	/*bShowMouseCursor = true;
	m_LButtonClick = false;
	m_SelectJob = EPlayerJob::End;
	m_SelectCharacter = nullptr;*/
}

void ASelectPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	//Picking();
	
}
void ASelectPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//InputComponent->BindAction(TEXT("CharacterSelect"), EInputEvent::IE_Pressed, this, & ASelectPlayerController::MouseClick);
	//InputComponent->BindAction(TEXT("CharacterSelect"), EInputEvent::IE_Released, this, & ASelectPlayerController::MouseRelease);

}

void ASelectPlayerController::MouseClick()
{
	/*m_LButtonClick = true; 

	if (m_SelectCharacter)
	{
		ACharacterSelectGameMode* GameMode =
			Cast<ACharacterSelectGameMode>(GetWorld()->GetAuthGameMode());

		if (GameMode)
		{
			ASelectPlayer* SelectPlayer = Cast<ASelectPlayer>(m_SelectCharacter);

			UCharacterSelectHUD* SelectHUD = GameMode->GetSelectHUD();

			if (SelectHUD)
			{
				SelectHUD->EnableStartButton(true);

				m_SelectJob = SelectPlayer->GetPlayerJob();

				UUEKR2GameInstance* GameInst = Cast<UUEKR2GameInstance>(GetWorld()->GetGameInstance());

				if (GameInst)
				{
					GameInst->SetSelectJob(m_SelectJob);
				}

				SelectHUD->SetInputNameVisibility(ESlateVisibility::SelfHitTestInvisible);

				switch (SelectPlayer->GetPlayerJob())
				{
				case EPlayerJob::Knight:
					SelectHUD->SetKnightStateVisibility(ESlateVisibility::SelfHitTestInvisible);
					SelectHUD->SetArcherStateVisibility(ESlateVisibility::Collapsed);
					break;
				case EPlayerJob::Archer:
					SelectHUD->SetKnightStateVisibility(ESlateVisibility::Collapsed);
					SelectHUD->SetArcherStateVisibility(ESlateVisibility::SelfHitTestInvisible);
					break;
				case EPlayerJob::Magicion:
					break;
				}
			}
		}
	}

	else
	{
		ACharacterSelectGameMode* GameMode =
			Cast<ACharacterSelectGameMode>(GetWorld()->GetAuthGameMode());

		if (GameMode)
		{
			UCharacterSelectHUD* SelectHUD = GameMode->GetSelectHUD();

			if (SelectHUD)
			{
				SelectHUD->SetInputNameVisibility(ESlateVisibility::Collapsed);
				SelectHUD->EnableStartButton(false);
				SelectHUD->SetKnightStateVisibility(ESlateVisibility::Collapsed);
				SelectHUD->SetArcherStateVisibility(ESlateVisibility::Collapsed);
			}
		}
	}*/
}
void ASelectPlayerController::MouseRelease()
{
	//m_LButtonClick = false;
}
void ASelectPlayerController::Picking()
{
	//FHitResult	result;

	//bool Hit = GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel9,
	//	false, result);

	//if (Hit)
	//{
	//	//LOG(TEXT("%s"), *result.GetActor()->GetName());
	//	ASelectPlayer* SelectPlayer = Cast<ASelectPlayer>(result.GetActor());

	//	if (SelectPlayer)
	//	{
	//		if (m_SelectCharacter != SelectPlayer)
	//		{
	//			if (m_SelectCharacter)
	//				m_SelectCharacter->GetMesh()->SetCustomDepthStencilValue(255);

	//			m_SelectCharacter = SelectPlayer;

	//			m_SelectCharacter->GetMesh()->SetCustomDepthStencilValue(1);
	//		}
	//	}
	//	
	//	else
	//	{
	//		if (m_SelectCharacter)
	//		{
	//			m_SelectCharacter->GetMesh()->SetCustomDepthStencilValue(255);
	//			m_SelectCharacter = nullptr;
	//		}
	//	}
	//}

	//else
	//{
	//	if (m_SelectCharacter)
	//	{
	//		m_SelectCharacter->GetMesh()->SetCustomDepthStencilValue(255);
	//		m_SelectCharacter = nullptr;
	//	}
	//}
}