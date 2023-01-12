#include "PreCompile.h"
#include "DBQueue.h"
#include <GameServerNet\DBConnecter.h>
#include "GameServerCore.h"
#include <GameServerNet\RedisConnecter.h>
#include <GameServerContents/UserTable.h>
DBQueue* DBQueue::Inst_ = new DBQueue();

// GameServerQueue DBQueue::JobQueue = GameServerQueue();

DBQueue::DBQueue()
{

}

DBQueue::~DBQueue()
{
	JobQueue.Destroy();
}

std::mutex ConnectionRock;

void InitDBConnecter()
{
	// �����忡 �������� ���� ���� Ŀ��Ʈ ȣ���� ������ �ɼ� �����Ƿ�
	// ���� �Ǵ�.
	ConnectionRock.lock();

	DBConnecter::InitConnector(GameServerCore::GetDBHost(),
		GameServerCore::GetDBUser(),
		GameServerCore::GetDBPW(),
		GameServerCore::GetDBName(),
		GameServerCore::GetDBPort());

	RedisConnecter::InitConnector("127.0.0.1", 6379);

	ConnectionRock.unlock();
}

void DBQueue::Init()
{
	Inst_->JobQueue.Initialize(GameServerQueue::WORK_TYPE::Default, 20, "DBThread", InitDBConnecter);
}

void DBQueue::Queue(const std::function<void()>& CallBack)
{
	Inst_->JobQueue.EnQueue(CallBack);
}

void DBQueue::Destroy()
{
	Queue([=]
		{
			UserTable_UpdateAll_ConnectStatus UpdateQuery = UserTable_UpdateAll_ConnectStatus();

			if (false == UpdateQuery.DoQuery())
				GameServerDebug::Log(LOGTYPE::LOGTYPE_WARNING, "Ŭ���̾�Ʈ�� ���� ���� ���� ���Ͽ����ϴ�.");
		});


	if (nullptr != Inst_)
	{
		delete Inst_;
	}
}