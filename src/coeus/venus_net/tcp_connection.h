#ifndef __TCP_CONNECTION_H__
#define __TCP_CONNECTION_H__

#include "common.h"
#include "basic_stream.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketReactor.h"
#include "network_message.h"
#include "message_queue.h"

class TcpConnection : public Poco::Net::TCPServerConnection
{
    static const int MAX_RECV_LEN = 1024 * 4;

public:
    TcpConnection(const Poco::Net::StreamSocket& socket, MessageQueue& messageQueue);
    virtual ~TcpConnection();
    void run();

public:
    void sendMessage(const BasicStreamPtr& packet);
	void sendMessage(int16 opcode, const byte* buff, size_t size);
	void sendMessage(uint16 opcode, NetworkMessage& message);

private:
    enum ShutdownReason
    {
        SR_GRACEFUL_SHUTDOWN,
        SR_EXCEPTION
    };

    bool onReadable();
    void onShutdown(const ShutdownReason& reason);
    void addPending(const byte* buff, size_t len);
    bool checkMessageLen(size_t len);

private:
    byte* _buffer;
    BasicStreamPtr _pendingStream;      //��Ž��յ�������
    BasicStreamPtr _packetStreamPtr;    //���һ�����������ݰ�
    Poco::Net::StreamSocket& _socket;
    MessageQueue& _messageQueue;
    mutable Poco::FastMutex _mutex;
};

#endif // !__TCP_CONNECTION_H__
