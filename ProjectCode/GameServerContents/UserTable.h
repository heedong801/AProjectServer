#pragma once
#include <GameServerNet\DBQuery.h>

class UserRow : public std::enable_shared_from_this<UserRow>
{
public:
	int			Index;
	std::string Id;
	std::string Pw;
	int			ConnectStatus;

public:
	UserRow() 
	{
	}

	UserRow(
		int _Index,
		std::string _Id,
		std::string _Pw,
		int			_ConnectStatus
	)
		:Index(_Index),
		Id(_Id),
		Pw(_Pw),
		ConnectStatus(_ConnectStatus)
	{
	}
};

class UserTable_SelectIDToUserInfo : public DBQuery
{
public:
	std::string ID;
	std::shared_ptr<UserRow> RowData;

public:
	UserTable_SelectIDToUserInfo(std::string _ID);
	bool DoQuery() override;
};


class UserTable_AllUserInfo : public DBQuery
{
public:
	std::vector<std::shared_ptr<UserRow>> RowDatas;

public:
	UserTable_AllUserInfo();

	bool DoQuery() override;
};

class UserTable_InsertUserInfo : public DBQuery
{
	std::string ID;
	std::string PW;

public:
	UserTable_InsertUserInfo(std::string _ID, std::string _PW);

	bool DoQuery() override;
};

class UserTable_UpdateUserInfo : public DBQuery
{
	std::string ID;
	int ConnectStatus;

public:
	UserTable_UpdateUserInfo(std::string _ID, int _ConnectStatus);

	bool DoQuery() override;
};