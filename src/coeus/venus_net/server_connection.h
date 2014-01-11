#ifndef __SERVER_SESSION_H__
#define __SERVER_SESSION_H__

#include "common.h"

// ServerConnection �������صײ�Connection�Ĳ��ֽӿ�
// �ṩ�����������ϲ�����ӽ��в���

class TcpConnection;
class NetworkMessage;
class ServerConnection
{
public:
    ServerConnection(TcpConnection* connection);
    virtual ~ServerConnection();

public:
    void sendMessage(uint16 opcode, NetworkMessage& message);
    void close();

private:
    TcpConnection* _connection;
};

#endif