#ifndef __GAME_DATABASE_H__
#define __GAME_DATABASE_H__

#include "venus_net/venus_net.h"
#include "venus_net/singleton.h"
#include "Poco/Data/Common.h"
#include "Poco/Data/SQLite/Connector.h"
#include "Poco/Data/RecordSet.h"
#include "Poco/Data/SessionFactory.h"

class PlayerDB;

class GameDatabase
    : public Venus::Singleton<GameDatabase>
{
public:
    GameDatabase();
    virtual ~GameDatabase();

public:
    //====================================================================
    // �û�ϵͳϵͳ
    //====================================================================

    //������ݿ���һ���û��Ƿ����
    bool checkUserExists(const std::string& username);

    //��֤�ʺź������Ƿ�ƥ��
    bool userAuth(const std::string& username, const std::string& password);

    //�����µ��û���¼
    void insertNewUserRecord(
        uint64 guid, 
        const std::string& username,
        const std::string& password,
        const std::string& register_ip,
        uint64 register_timestamp
        );

    //====================================================================
    // ��ɫ���
    //====================================================================

    //�����ǳ��Ƿ����
    bool checkNicknameExist(const std::string& nickname);

    bool loadPlayerInfo(uint64 guid, PlayerDB* playerDB);
    bool savePlayerInfo(uint64 guid, PlayerDB* playerDB);
private:
    Poco::Data::Session* _db_session;
    Poco::Data::Statement* _db_stmt;
};

#endif