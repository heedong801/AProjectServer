#include "PreCompile.h"
#include "GameServerIocp.h"
#include <Windows.h>
#include "GameServerDebug.h"
#include "GameServerThread.h"

GameServerIocpWorker::GameServerIocpWorker(HANDLE _IocpHandle, size_t _Index, DWORD _time)
	: IocpHandle(_IocpHandle)
	, Time(_time)
	, Index(_Index)
{
}


BOOL GameServerIocpWorker::Wait()
{
	//BOOL ReturnValue = GetQueuedCompletionStatus(IocpHandle, &NumberOfBytesTransferred, &CompletionKey, &lpOverlapped, Time);

	//if (0 == ReturnValue )
	//{
	//	if (WAIT_TIMEOUT == GetLastError())
	//	{
	//		return IocpWaitReturnType::RETURN_TIMEOUT;
	//	}

	//	return IocpWaitReturnType::RETURN_ERROR;
	//}

	// NetWorkBind를 할때 CompletionKey와 소켓을 연결한다.
	// => 앞으로 소켓에 무슨일이 생겨서 이 함수가 리턴되면 
	// CompletionKey가 나올거다.
	// 그 소켓들은 감시 받게 되었어
	// 진짜 일들이 있어요?


	// AcceptEx
	// WsaRecv
	// WsaSend
	// OverLapped 들을 넣어준다.
	// 호출할때마다 다른 오브랩드들을

	// TranmitFile (디스커넥트)
	// OverLappet

	// CompletionKey => OverlappedJOB 
	// lpOverlapped => AcceptExOverapped
	//              => SendExOverapped


	// 한 소켓에 send와 리시브가 동시에 일어날수 있잖아요?
	// 그걸 동시에 처리하려는게 비동기잖아요!!!
	// 

	return GetQueuedCompletionStatus(IocpHandle, &NumberOfBytesTransferred, &CompletionKey, &lpOverlapped, Time);
}

GameServerIocp::~GameServerIocp()
{
	for (size_t i = 0; i < threadList_.size(); i++)
	{
		threadList_[i]->join();
	}
}

GameServerIocp::GameServerIocp()
	: Iocp_(NULL)
{

}

GameServerIocp::GameServerIocp(GameServerIocp&& _Other) noexcept
{

}

void GameServerIocp::InitializeIocpHandle(int Count)
{
	Iocp_ = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, Count);
}

void GameServerIocp::Initialize(std::string ThreadName,
	std::function<void(std::shared_ptr<GameServerIocpWorker>)> _Func,
	std::function<void()> _Init,
	std::function<void()> _End,
	DWORD _Time,
	int threadCount)
{
	// 윈도우 종속적
	if (128 <= threadCount)
	{
		return;
	}

	if (0 >= threadCount)
	{
		SYSTEM_INFO Info;
		GetSystemInfo(&Info);
		threadCount = Info.dwNumberOfProcessors;
	}

	InitializeIocpHandle(threadCount);

	for (int i = 0; i < threadCount; i++)
	{
		AddThread(ThreadName, _Func, _Init, _End, _Time, i);
	}
}

void GameServerIocp::AddThread(std::string _Name, std::function<void(std::shared_ptr<GameServerIocpWorker>)> _Func, std::function<void()> _InitFunction, std::function<void()> _EndFunction, DWORD _Time, unsigned int _Order = 0)
{
	iocpLock.lock();
	std::shared_ptr<GameServerIocpWorker> NewWork = std::make_shared<GameServerIocpWorker>(Iocp_, threadWorkerList_.size(), _Time);
	threadWorkerList_.push_back(NewWork);
	std::shared_ptr<GameServerThread> NewThread = std::make_shared<GameServerThread>(_Name, std::bind(_Func, NewWork), _InitFunction, _EndFunction);
	threadList_.push_back(NewThread);
	NewThread->SetThreadOrder(_Order);
	iocpLock.unlock();
}

void GameServerIocp::Post(DWORD _byteSize, ULONG_PTR _Data)
{
	// 그냥 어떠한 8바이트를 날려주는거야
	// 우리가 동적할당해서 날려줬죠?
	// 이녀석은 지워야한다.
	PostQueuedCompletionStatus(Iocp_, _byteSize, _Data, nullptr);
}

bool GameServerIocp::Bind(HANDLE _Handle, ULONG_PTR _CompletionKey) const
{
	// 소켓과 하나의 8바이트 값이 링크가 되죠?
	// 8바이트 값은 우리가 동적할당해서 넣어줬지만
	// _Handle 소켓에 무슨 일이 생길때마다 8바이트 우리에게 제공될 것이다.
	// 이녀석을 삭제하면
	// 리시브가 한번만 되나요? 계속 앞으로 리시브 할건데.
	// 우리가 지워버리면?????????????
	if (Iocp_ != CreateIoCompletionPort(_Handle, Iocp_, _CompletionKey, 0))
	{
		return false;
	}

	return true;
}

BOOL GameServerIocp::Execute(DWORD& NumberOfBytesTransferred, ULONG_PTR& CompletionKey, LPOVERLAPPED& lpOverlapped, DWORD _Time)
{
	return GetQueuedCompletionStatus(Iocp_, &NumberOfBytesTransferred, &CompletionKey, &lpOverlapped, _Time);
}

BOOL GameServerIocp::ExecuteEx(LPOVERLAPPED_ENTRY _Entry, PULONG _ulNumEntriesRemoved, DWORD _TimeOut)
{
	return GetQueuedCompletionStatusEx(Iocp_, _Entry, 16, _ulNumEntriesRemoved, _TimeOut, FALSE);
}