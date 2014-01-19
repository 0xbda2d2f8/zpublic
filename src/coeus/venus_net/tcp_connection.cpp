#include "tcp_connection.h"
#include "Poco/Util/Application.h"
#include "Poco/Timespan.h"
#include "service_application.h"
#include "logger.h"
#include "message_notification.h"
#include "stream_writer.h"
#include "stream_reader.h"
#include "message_queue.h"
#include "server_connection.h"

TcpConnection::TcpConnection(const Poco::Net::StreamSocket& socket, MessageQueue& messageQueue, uint32 sequence)
    : Poco::Net::TCPServerConnection(socket),
    _socket(const_cast<Poco::Net::StreamSocket&>(socket)),
    _buffer(new byte[MAX_RECV_LEN]),
    _blockPacketization(std::bind(&TcpConnection::finishedPacketCallback, this, std::placeholders::_1)),
    _messageQueue(messageQueue),
    _sequence(sequence),
    _serverConnection(nullptr),
    _state(ConnectionState::None)
{
    _socket.setBlocking(false);
    _socket.setReuseAddress(true);
    _socket.setReusePort(true);
}

TcpConnection::~TcpConnection()
{
    SAFE_DELETE_ARR(_buffer);
    SAFE_DELETE(_serverConnection);
    debug_log("connection destroyed.");
}

void TcpConnection::run()
{
    _state = ConnectionState::Established;

    try
    {
        _serverConnection = new ServerConnection(this);
        _messageQueue.dispatcher()->onNewConnection(_serverConnection);
        
        for (;;)
        {
			bool readable = _socket.poll(Poco::Timespan(0, 0), Poco::Net::Socket::SelectMode::SELECT_READ);
            if (_state == ConnectionState::Established)
            {
                if (readable == true)
                {
                    bool stateResult = onReadable();
                    if (stateResult == false)
                    {
                        _state = ConnectionState::ClosedWait;
                    }
                }
            }
            else
            {
                return;
            }
        }
    }
    catch (Poco::Exception& e)
    {
        error_log("Poco::Exception : %s", e.what());
        onShutdown(ShutdownReason::SR_EXCEPTION);
    }
    catch (...)
    {
        error_log("unknown exception.");
        onShutdown(ShutdownReason::SR_EXCEPTION);
    }
}


void TcpConnection::sendMessage(const BasicStreamPtr& stream)
{
    if (_state == ConnectionState::Established)
    {
        _socket.sendBytes((const void*)stream->b.begin(), stream->b.size());
    }
}

void TcpConnection::sendMessage(int16 opcode, const byte* buff, size_t size)
{
    BasicStreamPtr streamPtr(new BasicStream());

    streamPtr->write((int32)0); //����Ԥ��
    streamPtr->write(opcode);   //������
    // ...
    // TODO: ��ѹ���ͼ��ܱ�־Ԥ��

    streamPtr->append((const byte*)buff, size);
    streamPtr->rewriteSize(streamPtr->b.size(), streamPtr->b.begin());

    sendMessage(streamPtr);
}

void TcpConnection::sendMessage(uint16 opcode, NetworkMessage& message)
{
    BasicStreamPtr streamPtr(new BasicStream());
    streamPtr->write((int32)0);
    streamPtr->write(opcode);
    // ...
    // TODO: ��ѹ���ͼ��ܱ�־Ԥ��

    streamPtr->resize(NetworkParam::kHeaderLength + message.byteSize());
    message.encode((byte*)streamPtr->b.begin() + NetworkParam::kHeaderLength, message.byteSize());
    streamPtr->rewriteSize(streamPtr->b.size(), streamPtr->b.begin());

    sendMessage(streamPtr);
}

// ����false��ζ�������ѱ��Զ˹ر�
bool TcpConnection::onReadable()
{
    int bytes_transferred = _socket.receiveBytes(_buffer, MAX_RECV_LEN, 0);
    if (bytes_transferred == 0)
    {
        onShutdown(ShutdownReason::SR_PEER_GRACEFUL_SHUTDOWN);
        return false;
    }
    else
    {
        bool result = _blockPacketization.appendBlock(_buffer, bytes_transferred);
        if (result == false)
        {
            onShutdown(ShutdownReason::SR_SERVICE_PACKET_FAILURE);
            return false;
        }

        return true;
    }
}

void TcpConnection::onShutdown(const ShutdownReason& reason)
{
    switch (reason)
    {
    case ShutdownReason::SR_SERVICE_CLOSE_INITIATIVE:
        {
            debug_log("service close connection initiative.");
            break;
        }
    case ShutdownReason::SR_PEER_GRACEFUL_SHUTDOWN:
        {
            debug_log("connection graceful shutdown from the peer.");
            break;
        }
    case ShutdownReason::SR_EXCEPTION:
        {
            debug_log("connection exception, maybe reset from peer.");
            break;
        }
    default:
        break;
    }

    //����ر����ӵ���Ϣ��Ӧ�ò�
    Poco::Notification::Ptr notification(new CloseNotification(_serverConnection, reason));
    _messageQueue.enqueueNotification(notification);

    //_messageQueue.dispatcher()->onShutdown(_serverConnection, reason);
    //_socket.shutdown();
    _socket.close();
}

void TcpConnection::finishedPacketCallback(BasicStreamPtr& packet)
{
    //����������Ϣ����Ӧ�ò�
    uint16 opcode = 0;
    packet->read(opcode);

    NetworkPacket::Ptr packetPtr(new NetworkPacket);
    packetPtr->opcode = opcode;
    packetPtr->message = NetworkPacket::PDU(packet->b.begin() + NetworkParam::kHeaderLength, packet->b.end());

    //����������Ϣ����Ӧ�ò�
    // ...
    Poco::Notification::Ptr notification(new MessageNotification(_serverConnection, packetPtr));
    _messageQueue.enqueueNotification(notification);
}

void TcpConnection::close(const ShutdownReason& reason)
{
    onShutdown(reason);
}