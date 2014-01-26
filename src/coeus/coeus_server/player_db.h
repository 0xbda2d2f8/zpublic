#ifndef __DB_PLAYER_H__
#define __DB_PLAYER_H__

#include <common.h>
#include "game_database.h"
#include "data_cached.h"

class PlayerDB : public DataCached
{
public:
    bool loadFromDB(uint64 guid);
    void cleanup();

public:
    std::string email;          //���������ʺ�
    uint8 gender;               //�Ա�
    std::string nickname;       //�ǳ�
    std::string register_ip;    //ע��IP
    int64 register_time;        //ע��ʱ��
    int64 last_login;           //�ϴε�¼ʱ��
};

#endif