#ifndef __SERVER_CONFIG_H__
#define __SERVER_CONFIG_H__

#include "game_common/config/configuration.h"

class ServerConfig
	: public Configuration, public Venus::Singleton<ServerConfig>
{
public:
    std::string serviceName;        //��Ϸ��������
    std::string listenAddress;      //��Ϸ���������ַ, ����0.0.0.0:36911
    int32 maxQueued;                //������Ӷ���
    int32 maxThreads;               //���I/O�߳�
    std::string phpServerAddress;   //PHP��̨����ĵ�ַ, ����127.0.0.1:19527
    std::string sqlite3File;        //sqlite3���ݿ��ļ�·��

public:
	bool parse();
};

#endif