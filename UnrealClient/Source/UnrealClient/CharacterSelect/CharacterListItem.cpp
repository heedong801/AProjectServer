// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterListItem.h"
#include "../Message/Messages.h"
#include "../Global/ClientBlueprintFunctionLibrary.h"
#include "../Global/ClientGameInstance.h"

void UCharacterListItem::CharacterSelect()
{
	UClientGameInstance* Inst = Cast<UClientGameInstance>(GetGameInstance());

	std::string ConvertNickName;
	UClientBlueprintFunctionLibrary::FStringToUTF8(NickName, ConvertNickName);

	Inst->NickName = NickName;
	Inst->NickNameUTF8 = ConvertNickName;

	/*SelectCharacterMessage NewPacket;
	NewPacket.NickName = ConvertNickName;
	GameServerSerializer Sr;
	NewPacket.Serialize(Sr);

	if (false != Inst->Send(Sr.GetData()))
	{
		int a = 0;
	}*/

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Select"));

}