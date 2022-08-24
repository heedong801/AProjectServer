#pragma once
#include "ContentsStructure.h"
#include "ItemTable.h"
#include <GameServerBase\GameServerObjectBase.h>

class ContentsItemData : public GameServerObjectBase
{
public:
	ContentsItemData();
	~ContentsItemData();

	ContentsItemData(const ContentsItemData& _Other) = delete;
	ContentsItemData(ContentsItemData&& _Other) noexcept = delete;
	ContentsItemData& operator=(const ContentsItemData& _Other) = delete;
	ContentsItemData& operator=(ContentsItemData&& _Other) noexcept = delete;

	static FPlayerItemData GetItemAtIndex(int idx);
	static void AddItemData(FPlayerItemData item);
protected:

private:
	static std::vector<FPlayerItemData> Items;

};

////enum class EItemPart : uint8
//{                             4                                          10
//	NONE, HEADBAND, HEAD, EYE, NECK, FACE, SHOULDER, ARMOR, CHEST, BODY, MAINHAND, MAINWRIST, BELT, OFFWRIST, OFFHAND,
//		HAND, TROUSERS, RING, FEET
//};