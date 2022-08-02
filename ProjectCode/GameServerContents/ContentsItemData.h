#pragma once
#include "ContentsStructure.h"
#include "ItemTable.h"
#include <GameServerBase\GameServerObjectBase.h>

class ContentsItemData : public GameServerObjectBase
{

public:
	//UserRow Data;
	//std::vector<FCharacterInfo> Characters;
	//FCharacterInfo SelectData;

	// constrcuter destructer
	ContentsItemData();
	~ContentsItemData();

	// delete Function
	ContentsItemData(const ContentsItemData& _Other) = delete;
	ContentsItemData(ContentsItemData&& _Other) noexcept = delete;
	ContentsItemData& operator=(const ContentsItemData& _Other) = delete;
	ContentsItemData& operator=(ContentsItemData&& _Other) noexcept = delete;

protected:

private:

};

