#pragma once
#include <GameServerCore\ThreadHandlerBase.h>
#include "ClientToServer.h"
#include "ServerToClient.h"

class ThreadHandlerGetInventoryMessage final
	: public ThreadHandlerBase<GetInventoryMessage>
{
	GetInventoryResultMessage Result_;
	GetEquipmentResultMessage EquipResult_;

public:
	ThreadHandlerGetInventoryMessage();
	~ThreadHandlerGetInventoryMessage();

	ThreadHandlerGetInventoryMessage(const ThreadHandlerGetInventoryMessage& _Other) = delete;
	ThreadHandlerGetInventoryMessage(ThreadHandlerGetInventoryMessage&& _Other) noexcept = delete;
	ThreadHandlerGetInventoryMessage& operator=(const ThreadHandlerGetInventoryMessage& _Other) = delete;
	ThreadHandlerGetInventoryMessage& operator=(ThreadHandlerGetInventoryMessage&& _Other) noexcept = delete;

	void Start() override;
	void DBCheck();

	void ResultSend();
protected:

private:

};

