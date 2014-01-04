#ifndef __NETWORK_MESSAGE_H__
#define __NETWORK_MESSAGE_H__

#include "common.h"

struct NetworkMessage
{
public:
    const static uint8 kMagicFlagLength = 4;            //��Ϣ����ǰ���ʾ���ܳ��ȵ��ֽ���
    const static uint8 kHeaderLength = 8;               //���ȺͲ�����
    const static int32 kMaxMessageLength = 10 * 65535;  //��Ϣ��󳤶�

    NetworkMessage(){}
    virtual ~NetworkMessage(){}

    virtual int32 byteSize() = 0;
    virtual void encode(byte* buffer, size_t size) = 0;
    virtual void decode(const byte* buffer, size_t size) = 0;
};

#endif // !__NETWORK_MESSAGE_H__
