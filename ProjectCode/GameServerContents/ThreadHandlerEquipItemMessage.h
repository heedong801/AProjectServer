#pragma once
#include <GameServerCore\ThreadHandlerBase.h>
#include "ClientToServer.h"
// �뵵 : 
// �з� :
// ÷�� : 
class ThreadHandlerEquipItemMessage final
	: public ThreadHandlerBase<EquipItemMessage>
{
private: // Member Var

public: // Default
	ThreadHandlerEquipItemMessage();
	~ThreadHandlerEquipItemMessage();

	ThreadHandlerEquipItemMessage(const ThreadHandlerEquipItemMessage& _Other) = delete;
	ThreadHandlerEquipItemMessage(ThreadHandlerEquipItemMessage&& _Other) noexcept;

protected:
	ThreadHandlerEquipItemMessage& operator=(const ThreadHandlerEquipItemMessage& _Other) = delete;
	ThreadHandlerEquipItemMessage& operator=(ThreadHandlerEquipItemMessage&& _Other) = delete;

private:

public: // Member Function

	void Start() override;
	void DBCheck();

};

