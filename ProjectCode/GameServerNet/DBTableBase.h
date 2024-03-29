#pragma once
#include "DBConnecter.h"

// ���� :
class DBTableBase
{
public:
	// constrcuter destructer
	DBTableBase();
	~DBTableBase();

	// delete Function
	DBTableBase(const DBTableBase& _Other) = delete;
	DBTableBase(DBTableBase&& _Other) noexcept = delete;
	DBTableBase& operator=(const DBTableBase& _Other) = delete;
	DBTableBase& operator=(DBTableBase&& _Other) noexcept = delete;

};

