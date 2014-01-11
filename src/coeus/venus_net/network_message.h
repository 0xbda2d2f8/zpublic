#ifndef __NETWORK_MESSAGE_H__
#define __NETWORK_MESSAGE_H__

#include "common.h"
#include "Poco/AutoPtr.h"
#include "Poco/RefCountedObject.h"

struct NetworkParam
{
    const static uint8 kMagicFlagLength = 4;            //��Ϣ����ǰ���ʾ���ܳ��ȵ��ֽ���
    const static uint8 kHeaderLength = 8;               //���ȺͲ�����
    const static int32 kMaxMessageLength = 10 * 65535;  //��Ϣ��󳤶�
};

// ����ʵ�����˵���Ϣ����̳д���
// ��Ϣ����Ҫ��дbyteSize/encode/decode��������
class NetworkMessage
{
public:
    NetworkMessage(){}
    virtual ~NetworkMessage(){}

    virtual int32 byteSize() = 0;
    virtual void encode(byte* buffer, size_t size) = 0;
    virtual void decode(const byte* buffer, size_t size) = 0;
};

// NetworkPacket�����ڰ�װ�����յ���������
// ���͵��ϲ�ʱ��Ҫ��NetworkPacket��ȡ�������з����л��õ��������Ϣ�ṹ
struct NetworkPacket : Poco::RefCountedObject
{
    typedef Poco::AutoPtr<NetworkPacket> Ptr;
    typedef std::vector<byte> PDU;

    uint16 opcode;
    PDU messageBody;
};

#define DECODE_MESSAGE(message, data) \
    message.decode((const byte*)&data->messageBody[0], data->messageBody.size());


#endif // !__NETWORK_MESSAGE_H__
