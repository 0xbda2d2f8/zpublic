#include "tcp_client.h"

TcpClient::TcpClient()
    : _blockPacketization(std::bind(&TcpClient::onMessage, this, std::placeholders::_1)),
    _buffer(new byte[MAX_RECV_LEN])
{
    _reactor.addEventHandler(_socket, Poco::NObserver<TcpClient, Poco::Net::WritableNotification>(*this, &TcpClient::onWritable));
    _reactor.addEventHandler(_socket, Poco::NObserver<TcpClient, Poco::Net::ReadableNotification>(*this, &TcpClient::onReadable));
    _reactor.addEventHandler(_socket, Poco::NObserver<TcpClient, Poco::Net::ShutdownNotification>(*this, &TcpClient::onShutdown));
}

TcpClient::~TcpClient()
{
     _reactor.removeEventHandler(_socket, Poco::NObserver<TcpClient, Poco::Net::WritableNotification>(*this, &TcpClient::onWritable));
     _reactor.removeEventHandler(_socket, Poco::NObserver<TcpClient, Poco::Net::ReadableNotification>(*this, &TcpClient::onReadable));
     _reactor.removeEventHandler(_socket, Poco::NObserver<TcpClient, Poco::Net::ShutdownNotification>(*this, &TcpClient::onShutdown));
     _reactor.stop();
}

bool TcpClient::connect(Poco::Net::SocketAddress& address, const Poco::Timespan& timeout/* = Poco::Timespan(50000)*/)
{
    try
    {
        if (_reconnectFlag == false)
        {
            Poco::Thread thread;
            thread.start(_reactor);
        }

        _socket.close();
        _socket.connectNB(address);
        _reconnectFlag = true;
    }
    catch (Poco::TimeoutException& e)
    {
        std::cout << e.displayText() << std::endl;
        return false;
    }
    catch (Poco::Exception& e)
    {
        std::cout << e.displayText() << std::endl;
        Poco::AutoPtr<Poco::Net::ShutdownNotification> notification(new Poco::Net::ShutdownNotification(&_reactor));
        onShutdown(notification);
        return false;
    }

    return true;
}

void TcpClient::close()
{
    _socket.shutdown();
    _socket.close();
}

void TcpClient::sendMessage(const BasicStreamPtr& stream)
{
    bool writeable = _socket.poll(0, Poco::Net::Socket::SelectMode::SELECT_WRITE);
    bool error = _socket.poll(0, Poco::Net::Socket::SelectMode::SELECT_ERROR);

    if (writeable && !error)
    {
        _socket.sendBytes((const void*)stream->b.begin(), stream->b.size());
    }
}

void TcpClient::sendMessage(int16 opcode, const byte* buff, size_t size)
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

void TcpClient::sendMessage(uint16 opcode, NetworkMessage& message)
{
    BasicStreamPtr streamPtr(new BasicStream());
    streamPtr->write((int32)0);
    streamPtr->write(opcode);
    // ...
    // TODO: ��ѹ���ͼ��ܱ�־Ԥ��

    streamPtr->resize(NetworkMessage::kHeaderLength + message.byteSize());
    message.encode((byte*)streamPtr->b.begin() + NetworkMessage::kHeaderLength, message.byteSize());
    streamPtr->rewriteSize(streamPtr->b.size(), streamPtr->b.begin());

    sendMessage(streamPtr);
}

void TcpClient::onWritable(const Poco::AutoPtr<Poco::Net::WritableNotification>& notification)
{
    std::cout << "onWritable()" << std::endl;
}

void TcpClient::onReadable(const Poco::AutoPtr<Poco::Net::ReadableNotification>& notification)
{
    int bytes_transferred = _socket.receiveBytes(_buffer, MAX_RECV_LEN, 0);
    printf("received %d bytes.", bytes_transferred);
    if (bytes_transferred == 0)
    {
        _socket.close();
    }

    if (_blockPacketization.appendBlock(_buffer, bytes_transferred) == false)
    {
        _socket.close();
    }
}

void TcpClient::onShutdown(const Poco::AutoPtr<Poco::Net::ShutdownNotification>& notification)
{
    std::cout << "onShutdown()" << std::endl;
    delete this;
}

void TcpClient::onMessage(const BasicStreamPtr& packet)
{
    //����������Ϣ����Ӧ�ò�
    // ...
    //Poco::Notification::Ptr notification(new MessageNotification(packet));
    //_messageQueue.enqueueNotification(notification);
}