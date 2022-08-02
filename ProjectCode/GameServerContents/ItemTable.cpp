#include "PreCompile.h"
#include "ItemTable.h"

UserTable_SelectItemToItemInfo::UserTable_SelectItemToItemInfo(int _Index)
	: DBQuery("SELECT Name, Overlap, ItemType, ItemTier, ItemPart, Desc FROM userver2.iteminfo WHERE Index = ? LIMIT 1")
	, Index(_Index)
	, RowData(nullptr)
{
}

bool UserTable_SelectItemToItemInfo::DoQuery()
{
	// �� �� ���� �ø�ƽ�� �����޶�� �ؾ��ϴµ�.
	// �� �ø�ƽ�� �̹� ����ü�� �����˴ϴ�.
	// �� �ϰڴ�.
	std::unique_ptr<DBStmt> Stmt = DBConnecterPtr->CreateStmt(QueryString);

	Stmt->ParamBindInt(Index);

	std::unique_ptr<DBStmtResult> Result(Stmt->Execute());

	uint64_t Row = Result->AffectedRows();

	if (1 != Result->AffectedRows())
	{
		return false;
	}

	if (false == Result->Next())
	{
		return false;
	}

	RowData = std::make_shared<ItemRow>(Index,
		Result->GetString(0),
		Result->GetInt(1),
		Result->GetInt(2), 
		Result->GetInt(3),
		Result->GetInt(4),
		Result->GetString(5)
		);
	return true;
}