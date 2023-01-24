#include "ThreadHandlerLoginResultMessage.h"
#include "../../Global/ClientGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "../../Login/LoginUI.h"

void ThreadHandlerLoginResultMessage::Start()
{
	if (Inst_->LoginUI->IsValidLowLevel())
	{
		ULoginUI* loginUI = Cast<ULoginUI>(Inst_->LoginUI);
		if (IsValid(loginUI))
		{
			if (EGameServerCode::OK == Message_->Code)
			{
				loginUI->LoginStatus = TEXT("Login Success");

				// �������ʹ� ĳ���� ������ �ҷ����� ���Դϴ� ����â.
				// UGameplayStatics::OpenLevel(World_, TEXT("CharacterSelectLevel"));
				return;
			}
			else if (EGameServerCode::AlreadyPlay == Message_->Code)
			{
				loginUI->LoginStatus = TEXT("Already Play");
			}

			// �����ѰŴϱ� �ٽ� �α����� �����ϴ�.
			Inst_->LoginProcess_ = false;
		}
	}
	// �α��� ui
}

