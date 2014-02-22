#ifndef __DB_PLAYER_H__
#define __DB_PLAYER_H__

#include "venus_net/venus_net.h"
#include "game_database.h"

class PlayerDB
{
public:
    PlayerDB()
    {
        cleanup();
    }

	void cleanup()
	{
        email = "";
		gender = 0;
        nickname = "";
        register_ip = "";
		register_time = 0;
		last_login = 0;
	}

    std::string email;          //���������ʺ�
    uint8 gender;               //�Ա�
    std::string nickname;       //�ǳ�
    std::string register_ip;    //ע��IP
    int64 register_time;        //ע��ʱ��
    int64 last_login;           //�ϴε�¼ʱ��
};

#endif