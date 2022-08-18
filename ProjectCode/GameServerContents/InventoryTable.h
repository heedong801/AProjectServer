#pragma once
#include <GameServerNet\DBQuery.h>

class InventoryRow : public std::enable_shared_from_this<InventoryRow>
{
public:
	int			CharacterIdx_;
	int			ItemIdx_;

public:
	InventoryRow()
	{
	}

	InventoryRow(
		int _Index,
		int _ItemIdx
	)
		:CharacterIdx_(_Index),
		ItemIdx_(_ItemIdx)
	{
	}
};

class InventoryTable_InsertItem : public DBQuery
{
public:
	int CharacterId_;
	int ItemId_;
public:
	InventoryTable_InsertItem(int _Id, int _ItemId);
	bool DoQuery() override;
};


class InventoryTable_SelectAllItem : public DBQuery
{
public:
	std::vector<std::shared_ptr<InventoryRow>> RowDatas;
	int CharacterId_;
public:
	InventoryTable_SelectAllItem(int _Index);
	bool DoQuery() override;
};

