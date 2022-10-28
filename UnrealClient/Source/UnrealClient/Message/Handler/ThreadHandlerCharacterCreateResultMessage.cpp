#include "ThreadHandlerCharacterCreateResultMessage.h"
#include "../../Global/ClientGameInstance.h"
#include "../../CharacterSelect/CharacterListItemObject.h"
#include "../../Global/ClientBlueprintFunctionLibrary.h"
#include "Components/ListView.h"
#include "../../CharacterSelect/CharacterSelectUI.h"
void ThreadHandlerCharacterCreateResultMessage::Start()
{
	if (EGameServerCode::OK == Message_->Code)
	{
		Inst_->Characters_.push_back(Message_->ResultCharacter);
		UCharacterListItemObject* NewCharacterObject = NewObject<UCharacterListItemObject>();
		NewCharacterObject->Info = Message_->ResultCharacter;
		UClientBlueprintFunctionLibrary::UTF8ToFString(NewCharacterObject->Info.NickName, NewCharacterObject->ConvertNickName);
		Inst_->CharacterListView_->AddItem(NewCharacterObject);
		Inst_->CharacterListView_->SetScrollOffset(Inst_->CharacterListView_->GetNumItems() * 50.0f);

		UCharacterSelectUI* CharacterUI = Cast<UCharacterSelectUI>(Inst_->CharacterSelectUI);
		CharacterUI->CreateStatus = TEXT("Create Success");

	}
	else if(EGameServerCode::DuplicateID == Message_->Code)
	{
		UCharacterSelectUI* CharacterUI = Cast<UCharacterSelectUI>(Inst_->CharacterSelectUI);

		CharacterUI->CreateStatus = TEXT("Duplicate ID");
	}
}

