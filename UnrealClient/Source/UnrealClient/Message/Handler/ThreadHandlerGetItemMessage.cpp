
#include "ThreadHandlerGetItemMessage.h"
#include "../../Play/PlayGameMode.h"
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

