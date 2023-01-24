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

				// 이제부터는 캐릭터 정보를 불러오는 중입니다 서브창.
				// UGameplayStatics::OpenLevel(World_, TEXT("CharacterSelectLevel"));
				return;
			}
			else if (EGameServerCode::AlreadyPlay == Message_->Code)
			{
				loginUI->LoginStatus = TEXT("Already Play");
			}

			// 실패한거니까 다시 로그인이 가능하다.
			Inst_->LoginProcess_ = false;
		}
	}
	// 로그인 ui
}

