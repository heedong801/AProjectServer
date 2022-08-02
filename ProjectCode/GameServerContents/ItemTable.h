#pragma once
#include <GameServerNet\DBQuery.h>

class ItemRow : public std::enable_shared_from_this<ItemRow>
{
public:
	int			Index;
	std::string Name;
	int			Overlap;
	int			ItemType;
	int			ItemTier;
	int			ItemPart;
	std::string Desc;

public:
	ItemRow()
	{
	}

	ItemRow(
		int _Index,
		std::string _Name,
		int _Overlap,
		int _ItemType,
		int _ItemTire,
		int _ItemPart,
		std::string _Desc
	)
		:Index(_Index),
		Name(_Name),
		Overlap(_Overlap),
		ItemType(_ItemType),
		ItemTier(_ItemTire),
		ItemPart(_ItemPart),
		Desc(_Desc)
	{
	}
};

class UserTable_SelectItemToItemInfo : public DBQuery
{
public:
	int Index;
	std::shared_ptr<ItemRow> RowData;

public:
	UserTable_SelectItemToItemInfo(int _Index);
	bool DoQuery() override;
};