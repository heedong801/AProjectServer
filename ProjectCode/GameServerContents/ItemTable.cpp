#include "PreCompile.h"
#include "ItemTable.h"

ItemTable_AllItemToItemInfo::ItemTable_AllItemToItemInfo()
	: DBQuery("SELECT * FROM userver2.iteminfo")
{

}

bool ItemTable_AllItemToItemInfo::DoQuery()
{
	// �� �� ���� �ø�ƽ�� �����޶�� �ؾ��ϴµ�.
	// �� �ø�ƽ�� �̹� ����ü�� �����˴ϴ�.
	// �� �ϰڴ�.
	std::unique_ptr<DBStmt> Stmt = DBConnecterPtr->CreateStmt(QueryString);
	std::unique_ptr<DBStmtResult> Result(Stmt->Execute());

	uint64_t Row = Result->AffectedRows();
	RowDatas.reserve(Row);

	while (Result->Next())
	{
		RowDatas.push_back(
			std::make_shared<ItemRow>(Result->GetInt(0),
				Result->GetString(1),
				Result->GetInt(2),
				Result->GetInt(3),
				Result->GetInt(4),
				Result->GetInt(5),
				Result->GetString(6)));
	}
	return true;
}

