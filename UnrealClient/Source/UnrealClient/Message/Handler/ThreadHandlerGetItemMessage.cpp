
#include "ThreadHandlerGetItemMessage.h"
#include "../../Global/ClientGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "../../CharacterSelect/CharacterListItemObject.h"
#include "../../CharacterSelect/CharacterListItem.h"
#include "../../Global/ClientBlueprintFunctionLibrary.h"
#include "Components/ListView.h"
#include "../../UnrealClient.h"
#include "../../Play/PlayGameMode.h"
#include "../../Play/ClientCharacter.h"
#include "../../DebugClass.h"
void ThreadHandlerGetItemMessage::Start()
{
	APlayGameMode* PGameMode = Cast<APlayGameMode>(UGameplayStatics::GetGameMode(World_));

	if (nullptr == PGameMode
		|| false == PGameMode->IsValidLowLevel())
	{
		UE_LOG(ClientLog, Error, TEXT("%S(%u) > GameMode Is nullptr"), __FUNCTION__, __LINE__);
		return;
	}

	// 공통우리는 딱 하나의 로직만을 사용해서 그 규칙을 어기지 않는다
	// 어길 경우가 생기면 그건 무조건 예외로서 우리 모두가 알아야 한다.

	// 클라이언트가 다 들고 있을 겁니다.
	TSubclassOf<AClientCharacter> CharacterSubClass = PGameMode->GetOtherPlayerClass();

	if (nullptr == CharacterSubClass
		|| false == CharacterSubClass->IsValidLowLevel())
	{
		UE_LOG(ClientLog, Error, TEXT("%S(%u) > Character SubClass Is nullptr"), __FUNCTION__, __LINE__);
		return;
	}
	

	PGameMode->ObjectPushMessage(Message_->ItemData.ObjectIndex, Message_);
	
}

