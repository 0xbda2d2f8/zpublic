#ifndef __DB_PLAYER_H__
#define __DB_PLAYER_H__

#include "venus_net/venus_net.h"
#include "game_database.h"
#include "cached_object.h"

class PlayerDB
{
public:
    PlayerDB()
    {
        reset();
    }

	void reset()
	{
        email = "";
        register_ip = "";
		register_time = 0;
		last_login = 0;

        gender = 0;
        nickname = "";
	}

    //=======================================================
    // �û����
    //=======================================================
    std::string email;          //���������ʺ�
    std::string register_ip;    //ע��IP
    int64 register_time;        //ע��ʱ��
    int64 last_login;           //�ϴε�¼ʱ��

    //=======================================================
    // ��Ϸ��ɫ���
    //=======================================================
    uint64 player_id;           //��ɫΨһID
    uint8 gender;               //�Ա�
    std::string nickname;       //�ǳ�
};

#endif