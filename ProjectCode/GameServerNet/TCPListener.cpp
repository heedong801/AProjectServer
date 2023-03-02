#include "PreCompile.h"
#include "TCPListener.h"
#include "SocketAddress.h"
#include "ServerHelper.h"
#include "TCPSession.h"
#include "GameServerOverlapped.h"

TCPListener::TCPListener() 
	: ListenSocket_(NULL)
	, JobQueue_(nullptr)
	, AcceptCallBack_(nullptr)
{

}

TCPListener::~TCPListener() 
{

	int a = 0;

	connectionPool_;
	connections_;
	AcceptExOverlappedPool_;
	IocpAcceptExOverlappedPool_;
}

TCPListener::TCPListener(TCPListener&& _Other) noexcept
	: ListenSocket_(_Other.ListenSocket_)
{
}



bool TCPListener::Initialize(const IPEndPoint& _EndPoint, const std::function<void(std::shared_ptr<TCPSession>)>& _AcceptCallBack)
{
	ServerHelper::StartEngineStartUp();

	SocketAddress Addresss = _EndPoint.Serialize();

	// 비동기 액셉트를 하려는 소켓이다.
	ListenSocket_ = WSASocket(AF_INET, SOCK_STREAM, IPPROTO::IPPROTO_TCP, NULL, NULL, WSA_FLAG_OVERLAPPED);

	if (INVALID_SOCKET == ListenSocket_)
	{
		GameServerDebug::GetLastErrorPrint();
		return false;
	}

	// 접속 받는 쪽은 바인드를 해서 자신의 주소를 인지시켜야 합니다.
	int ErrorCode = ::bind(ListenSocket_, reinterpret_cast<const SOCKADDR*>(Addresss.GetBuffer()), static_cast<int>(Addresss.GetBufferLength()));

	if (SOCKET_ERROR == ErrorCode)
	{
		GameServerDebug::GetLastErrorPrint();
		Close();
		return false;
	}

	BOOL on = TRUE;

	ErrorCode = setsockopt(ListenSocket_, SOL_SOCKET, SO_CONDITIONAL_ACCEPT, reinterpret_cast<const char*>(&on), sizeof(on));
	if (SOCKET_ERROR == ErrorCode)
	{
		GameServerDebug::GetLastErrorPrint();
		Close();
		return false;
	}

	ErrorCode = listen(ListenSocket_, 1);
	if (SOCKET_ERROR == ErrorCode)
	{
		GameServerDebug::GetLastErrorPrint();
		Close();
		return false;
	}

	ListenEndPoint_ = _EndPoint;
	AcceptCallBack_ = _AcceptCallBack;
	return true;
}
void TCPListener::Close()
{
	if (NULL != ListenSocket_)
	{
		closesocket(ListenSocket_);
		ListenSocket_ = NULL;
	}
}

bool TCPListener::BindQueue(GameServerQueue& _JobQueue)
{
	JobQueue_ = &_JobQueue;

	return JobQueue_->NetWorkBind(ListenSocket_, std::bind(&TCPListener::OnAccept, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

}

void TCPListener::OnAccept(BOOL _Result, DWORD _ByteSize, LPOVERLAPPED _Overlapped)
{
	// 접속대기자 한명이 사라진것이니까.
	AsyncAccept();

	if (nullptr == _Overlapped)
	{
		return;
	}

	// 처리되고 나면 필요 없어요
	// 만약 이걸 누가 보관해서 썼다면 어차피 안지워 질것이고
	// 그게 아니라면 지워지니까.
	std::unique_ptr<AcceptExOverlapped> AcceptExOverPtr = std::unique_ptr<AcceptExOverlapped>(reinterpret_cast<AcceptExOverlapped*>(reinterpret_cast<char*>(_Overlapped) - sizeof(void*)));


	if (nullptr == AcceptCallBack_)
	{
		return;
	}

	if (_Result != 0)
	{
		AcceptExOverPtr->Execute(TRUE, _ByteSize);

		if (nullptr == AcceptCallBack_)
		{
			return;
		}


		// 프로토콜 앞으로 어떻게 통신할지 여기서 결정
		// 특정 인터페이스를 통해서
		// 우리는 무조건 앞에 1바이트 보내면서 하자.

		if (false == AcceptExOverPtr->GetTCPSession()->isAcceptBind_)
		{
			AcceptExOverPtr->GetTCPSession()->BindQueue(*JobQueue_);
			AcceptExOverPtr->GetTCPSession()->AcceptBindOn();
		}
		AcceptCallBack_(std::dynamic_pointer_cast<TCPSession>(AcceptExOverPtr->GetTCPSession()->shared_from_this()));


		AcceptExOverPtr->GetTCPSession()->RecvRequest();
		// 동기 리시브를
		// AcceptExOverPtr->
		// GetTCPSession() 
		// GetTCPSession()-

		connectsLock_.lock();
		connections_.insert(std::make_pair(AcceptExOverPtr->GetTCPSession()->GetConnectId(), AcceptExOverPtr->GetTCPSession()));
		connectsLock_.unlock();

		// 무조건 지워져야 한다.
		IocpAcceptExOverlappedPool_.Erase(AcceptExOverPtr.get());

		AcceptExOverlappedPool_.Push(AcceptExOverPtr.get());
		AcceptExOverPtr.release();
	}
	else 
	{
		GameServerDebug::AssertDebugMsg("Accept Error");
	}

}

// 만들어진 쓰레드 개수만큼
// _BackLog 몇명이나 접속대기를 시킬거냐
bool TCPListener::StartAccept(int _BackLog) 
{
	// 128명까지 한계로 보고 그 사이의 값이라면
	// 똑같이 코어개수만큼의 접속대기를 만들어 놓겠습니다.
	if (0 > _BackLog || 128 < _BackLog )
	{
		SYSTEM_INFO systemInfo;
		GetSystemInfo(&systemInfo);

		_BackLog = systemInfo.dwNumberOfProcessors;
	}

	// 접속대기 소켓을 등록시켜놓는다.
	for (size_t i = 0; i < _BackLog; i++)
	{
		// 연결은 안되어있는데 
		// 연결이 오면 그 연결을 받아가기 위한 소켓 _BackLog개수를 만든다는 이야기.
		AsyncAccept();
	}

	return true;

}

void TCPListener::AsyncAccept()
{

	PtrSTCPSession NewSession = nullptr;
	{
		// std::lock_guard<std::mutex> lock(connectPoolLock_);

		connectPoolLock_.lock();
		
		if (true == connectionPool_.empty())
		{
			NewSession = std::make_unique<TCPSession>();
			NewSession->Initialize();

			std::string LogText = std::to_string(static_cast<int>(NewSession->GetSocket()));
			GameServerDebug::LogInfo(LogText + " Socket Create");

			NewSession->SetParent(this);
		} 
		else 
		{
			// 여기에서 재활용된 소켓이겠죠?
			// 종료됐다고 그냥 이쪽에 안됩니다.
			// OK?
			NewSession = connectionPool_.front();
			std::string LogText = std::to_string(static_cast<int>(NewSession->GetSocket()));
			GameServerDebug::LogInfo(LogText + " Socket Reuse");
			connectionPool_.pop_front();
		}

		connectPoolLock_.unlock();
	}



	AcceptExOverlapped* AcceptOver = nullptr;/* = std::make_unique<AcceptExOverlapped>(NewSession)*/;
	{
		if (true == AcceptExOverlappedPool_.IsEmpty())
		{
			AcceptOver = new AcceptExOverlapped(NewSession);
		}
		else
		{
			AcceptOver = AcceptExOverlappedPool_.Pop();
			AcceptOver->SetTCPSession(NewSession);
		}
	}
	

	DWORD dwByte = 0;
	// 시작할때 패킷을 한번 받아볼수 있는 버퍼입니다.
	// 주소값도 같이 날아옵니다.

	// LPFN_ACCEPTEX를 통해서 라이브러리 없이도 포인터를 얻어올수도 있다.
	// sizeof(sockaddr_in) +16 Ip4 Ip6까지 
	// 제대로 종료가 안된 소켓을 보내면?
	BOOL Result = AcceptEx(ListenSocket_, NewSession->GetSocket(), AcceptOver->GetBuffer(), 0, sizeof(sockaddr_in) +16, sizeof(sockaddr_in) + 16, &dwByte, AcceptOver->GetOverlapped());
	IocpAcceptExOverlappedPool_.Push(AcceptOver);

	// 실패여도
	if (FALSE == Result)
	{
		// ERROR_IO_PENDING 비동기 IO을 하는 중이고 기다리는 중이다 에러
		if (ERROR_IO_PENDING != WSAGetLastError())
		{
			GameServerDebug::GetLastErrorPrint();
			return;
		}
	}
}

//class LockTest
//{
//	std::mutex Lock;
//public:
//	LockTest() {
//		Lock.lock();
//	}
//  ~LockTest() {
//		Lock.Unlock();
//	}
//};

void TCPListener::CloseSession(PtrSTCPSession _Session)
{
	// 여기까지 왔다는건 
	// 완전히 처리가 끝났다는 이야기입니다.
	
	// 이런 패턴을 많이 볼수 있습니다.
	{
		std::lock_guard<std::mutex> lock(connectsLock_);
		connections_ .erase(_Session->GetConnectId());
	}

	// 쓰레드랑 똑같은 원리
	{
		std::lock_guard<std::mutex> lock(connectPoolLock_);
		// 곧바로 다시 쓰려고 하는것
		connectionPool_.push_back(_Session);
	}
}

void TCPListener::BroadCast(std::vector<unsigned char> _Data, std::shared_ptr<TCPSession> _Ignore)
{
	connectsLock_.lock();
	for (auto& Session : connections_)
	{
		if (_Ignore == Session.second)
		{
			continue;
		}

		Session.second->Send(_Data);
	}
	connectsLock_.unlock();
}
