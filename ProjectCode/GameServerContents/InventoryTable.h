#pragma once
#include <GameServerNet\DBQuery.h>

class InventoryRow : public std::enable_shared_from_this<InventoryRow>
{
public:
	int			ItemIdx_;
	int			CharacterIdx_;

public:
	InventoryRow()
	{
	}

	InventoryRow(
		int _ItemIdx,
		int _Index
	)
		:ItemIdx_(_ItemIdx)
		,CharacterIdx_(_Index)
	{
	}
};

class InventoryTable_InsertItem : public DBQuery
{
public:
	int ItemId_;
	int CharacterId_;
public:
	InventoryTable_InsertItem(int _ItemId, int _Id);
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

