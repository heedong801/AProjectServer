#include "PreCompile.h"
#include "InventoryTable.h"

InventoryTable_InsertItem::InventoryTable_InsertItem(int _ItemId, int _Id)
	: DBQuery("INSERT INTO userver2.inventoryinfo (ItemIdx, CharacterIdx) VALUES (?, ?);")
	, ItemId_(_ItemId)
	, CharacterId_(_Id)
{
}

bool InventoryTable_InsertItem::DoQuery()
{
	std::unique_ptr<DBStmt> Stmt = DBConnecterPtr->CreateStmt(QueryString);

	Stmt->ParamBindInt(CharacterId_);
	Stmt->ParamBindInt(ItemId_);

	Stmt->Execute();

	uint64_t Row = Stmt->AffectedRows();

	if (0 == Row)
	{
		return false;
	}

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////

InventoryTable_SelectAllItem::InventoryTable_SelectAllItem(int _Index)
	: DBQuery("SELECT ItemIdx, CharacterIdx FROM userver2.inventoryinfo WHERE CharacterIdx = ?")
	, CharacterId_(_Index)
{
}

bool InventoryTable_SelectAllItem::DoQuery()
{
	std::unique_ptr<DBStmt> Stmt = DBConnecterPtr->CreateStmt(QueryString);

	Stmt->ParamBindInt(CharacterId_);

	std::unique_ptr<DBStmtResult> Result(Stmt->Execute());

	uint64_t Row = Result->AffectedRows();
	RowDatas.reserve(Row);

	while (Result->Next())
	{
		RowDatas.push_back
		(
			std::make_shared<InventoryRow>(InventoryRow(Result->GetInt(0), Result->GetInt(1)))
		);
	}

	return true;
}
