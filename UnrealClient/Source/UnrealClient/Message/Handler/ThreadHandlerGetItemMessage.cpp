
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

	// ����츮�� �� �ϳ��� �������� ����ؼ� �� ��Ģ�� ����� �ʴ´�
	// ��� ��찡 ����� �װ� ������ ���ܷμ� �츮 ��ΰ� �˾ƾ� �Ѵ�.

	// Ŭ���̾�Ʈ�� �� ��� ���� �̴ϴ�.
	TSubclassOf<AClientCharacter> CharacterSubClass = PGameMode->GetOtherPlayerClass();

	if (nullptr == CharacterSubClass
		|| false == CharacterSubClass->IsValidLowLevel())
	{
		UE_LOG(ClientLog, Error, TEXT("%S(%u) > Character SubClass Is nullptr"), __FUNCTION__, __LINE__);
		return;
	}
	

	PGameMode->ObjectPushMessage(Message_->ItemData.ObjectIndex, Message_);
	
}

