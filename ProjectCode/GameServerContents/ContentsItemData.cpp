#include "PreCompile.h"
#include "ContentsItemData.h"
#include "GameServerBase/GameServerDebug.h"

std::vector<FPlayerItemData> ContentsItemData::Items;
ContentsItemData::ContentsItemData()
{
}

ContentsItemData::~ContentsItemData()
{
}

FPlayerItemData ContentsItemData::GetItemAtIndex(int idx)
{
	if (idx < 0 || idx >= Items.size())
	{
		GameServerDebug::LogErrorAssert("������ idx�� �߸��Ǿ����ϴ�.");
	}

	return Items[idx];
}


void ContentsItemData::AddItemData(FPlayerItemData item)
{
	Items.push_back(item);
}
