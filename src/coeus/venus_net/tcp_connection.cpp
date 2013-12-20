#include "tcp_connection.h"
#include "Poco/Util/Application.h"
#include "Poco/Timespan.h"
#include "service_application.h"
#include "logger.h"

//Poco::FastMutex TcpConnection::_mutex;
TcpConnection::TcpConnection(const Poco::Net::StreamSocket& socket)
    : Poco::Net::TCPServerConnection(socket),
    _socket(const_cast<Poco::Net::StreamSocket&>(socket)),
    _buffer(new byte[MAX_RECV_LEN]),
    _pendingStream(new BasicStream())
{
    _socket.setBlocking(false);
    //_socket.setReuseAddress(true);
    //_socket.setReusePort(true);
    //_socket.setKeepAlive(true);
}

TcpConnection::~TcpConnection()
{
    SAFE_DELETE_ARR(_buffer);
    debug_log("connection destroyed.");
}

void TcpConnection::run()
{
    //Poco::ScopedLockWithUnlock<Poco::FastMutex> lock(_mutex);

    try
    {
        //Poco::Net::SocketAddress address = _socket.peerAddress();
        //std::string peer(address.toString());
        //debug_log("connection established. peer = %s", peer.c_str());
        sendMessage(10001, (const byte*)"hello", 5);
        for (;;)
        {
			bool readable = _socket.poll(Poco::Timespan(30, 0), Poco::Net::Socket::SelectMode::SELECT_READ);
			if (readable == true && onReadable() == false)
            {
                return;
            }
        }
    }
    catch (Poco::Exception& e)
    {
        onShutdown(ShutdownReason::SR_EXCETION);
    }
    catch (...)
    {
        error_log("unknown exception.");
    }
}


void TcpConnection::sendMessage(const BasicStreamPtr& stream)
{
    bool writeable = _socket.poll(0, Poco::Net::Socket::SelectMode::SELECT_WRITE);
    bool error = _socket.poll(0, Poco::Net::Socket::SelectMode::SELECT_ERROR);

    if (writeable && !error)
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

void TcpConnection::sendMessage(uint16 opcode, Message& message)
{
    BasicStreamPtr streamPtr(new BasicStream());
    streamPtr->write((int32)0);
    streamPtr->write(opcode);
    // ...
    // TODO: ��ѹ���ͼ��ܱ�־Ԥ��

    streamPtr->resize(Message::kHeaderLength + message.byteSize());
    message.encode((byte*)streamPtr->b.begin() + Message::kHeaderLength, message.byteSize());
    streamPtr->rewriteSize(streamPtr->b.size(), streamPtr->b.begin());

    sendMessage(streamPtr);
}

// ����false��ζ�������ѱ��Զ˹ر�
bool TcpConnection::onReadable()
{
    int bytes_transferred = _socket.receiveBytes(_buffer, MAX_RECV_LEN, 0);
    debug_log("received %d bytes.", bytes_transferred);
    if (bytes_transferred == 0)
    {
        onShutdown(ShutdownReason::SR_GRACEFUL_SHUTDOWN);
        return false;
    }

    for (int32 readIdx = 0; readIdx < bytes_transferred; )
    {
        int32 leftLen = bytes_transferred - readIdx;

        //δ�ﵽ���ȵ�4�ֽ�������ȴ�
        if (leftLen < Message::kMagicFlagLength && _pendingStream->b.size() == 0)
        {
            //�ѵ�ǰ���յ������ݼ��뻺��
            addPending((const byte*)(_buffer + readIdx), leftLen);
            return true;
        }

        //һ��������Ϣ����
        int32 msgLen = 0;

        //��Ҫ������Ϣ����
        int32 needReadLen = 0;

        //��Ÿ���Ϣ���ֽ���
        BasicStreamPtr streamPtr = new BasicStream();

        //����л����
        if (_pendingStream->b.size() > 0)
        {
            //֮ǰ���治��4�ֽ�
            if (_pendingStream->b.size() < Message::kMagicFlagLength)
            {
                //���ڻ�����4�ֽڣ�������
                if (_pendingStream->b.size() + leftLen < Message::kMagicFlagLength)
                {
                    //���Pending,������
                    addPending((const byte*)(_buffer + readIdx), leftLen);

                    return true;
                }

                //�������4�ֽڣ��Ȱ�4�ֽ�ʣ�µĲ���׷�ӵ�PendingStream��
                int32 srcPendingLen = _pendingStream->b.size();
                _pendingStream->append((const byte*)_buffer + readIdx, Message::kMagicFlagLength - _pendingStream->b.size());

                //��λ��ǰ��
                readIdx += (Message::kMagicFlagLength - srcPendingLen);

                //leftLen����
                leftLen = bytes_transferred - readIdx;
            }

            //�ȴӻ�����ж���������ʾ�ĳ���
            _pendingStream->i = _pendingStream->b.begin();
            _pendingStream->read(msgLen);

            //�����Ϣͷ�Ϸ���
            if (checkMessageLen(msgLen) == false) return false;

            //���������İ��������м�ĳ�ʱʱ�䲢�����ȴ�
            if (leftLen < (int32)(msgLen - _pendingStream->b.size()))
            {
                //���Pending��������
                addPending((const byte*)(_buffer + readIdx), leftLen);

                // TODO: �����´ν��ճ�ʱʱ��
                // ...

                return true;
            }

            //ʣ��Ҫ�������ݳ���
            needReadLen = msgLen - _pendingStream->b.size();

            //��PendingStreamȡ����
            streamPtr = _pendingStream;

            //���¿���һ��PendingStream��Ųа�
            _pendingStream = new BasicStream();
        }
        //û�л����
        else
        {
            //�ȶ�ȡ��Ϣ����
            msgLen = BasicStream::read((const byte*)_buffer + readIdx);

            //�����Ϣ���ȵĺϷ���
            if (checkMessageLen(msgLen) == false) return false;

            //���ʣ����ֽ������Ȳ��㣬��׷�ӵ�Pending�в�����
            if (leftLen < msgLen)
            {
                addPending((const byte*)(_buffer + readIdx), leftLen);
                return true;
            }
            needReadLen = msgLen;
        }

        //��ʼ����Ϣ��
        if (needReadLen > 0)
        {
            streamPtr->append((const byte*)(_buffer + readIdx), needReadLen);
        }

        streamPtr->i = streamPtr->b.begin() + Message::kMagicFlagLength;
        byte comp = 0;
        streamPtr->read(comp);

        //TODO:ѹ��Ԥ��
        if (comp > 0)
        {
        }

        //TODO::������Ԥ��
        byte encrypt = 0;
        streamPtr->read(encrypt);
        if (encrypt > 0)
        {
        }

        //TODO :����������Ϣ����Ӧ�ò�
        // ...

        readIdx += needReadLen;
    }

    return true;
}

void TcpConnection::onShutdown(const ShutdownReason& reason)
{
    switch (reason)
    {
    case ShutdownReason::SR_GRACEFUL_SHUTDOWN:
        {
            debug_log("connection graceful shutdown from the peer.");
            break;
        }
    case ShutdownReason::SR_EXCETION:
        {
            debug_log("connection exception.");
            break;
        }
    default:
        break;
    }
}

void TcpConnection::addPending(const byte* buff, size_t len)
{
    _pendingStream->append(buff, len);
}

bool TcpConnection::checkMessageLen(size_t len)
{
    if (len > Message::kMaxMessageLength)
    {
        error_log("message length too big");
        return false;
    }

    if (len < Message::kHeaderLength)
    {
        error_log("header length too small");
        return false;
    }

    return true;
}