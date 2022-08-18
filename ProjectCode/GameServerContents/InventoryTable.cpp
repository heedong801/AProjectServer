#include "PreCompile.h"
#include "InventoryTable.h"

InventoryTable_InsertItem::InventoryTable_InsertItem(int _Id, int _ItemId)
	: DBQuery("INSERT INTO userver2.Inventoryinfo (CharacterIdx, ItemIdx) VALUES (?, ?);")
	, CharacterId_(_Id)
	, ItemId_(_ItemId)
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
	: DBQuery("SELECT ItemIdx INTO userver2.Inventoryinfo WHERE CharacterIdx = ?")
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
