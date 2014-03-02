#ifndef __GAME_DEFINE_H__
#define __GAME_DEFINE_H__


enum Gender
{
    Female = 0,   // Ů��
    Male          // ����
};

enum Belief
{
    Holy = 0,           // ��ʥ��͢
    TechHarbinger,      // �Ƽ�����
    DarkBoundary,       // �ڰ��߽�
    BeliefMax
};

enum CharacterCareer
{
    MirrorHunter = 0,   // ��������
    Mechanic,           // ��еʦ
    CharacterCareerMax
};

enum LoginResult
{
    LR_LOGIN_SUCCESS,       // ��¼�ɹ�
    LR_ACCOUNT_DISMATCH,    // �û��������벻ƥ��
    LR_USER_BANNED,         // �û������
};

#endif // !__GAME_DEFINE_H__
