#ifndef __GAME_FG_BOARD_OBJECT_DEF
#define __GAME_FG_BOARD_OBJECT_DEF

typedef enum _emCardType
{
    emCardType_Null,
    emCardType_Stone,
    emCardType_Scissor,
    emCardType_Cloth,
}emCardType;

#include <vector>
#include <string>

/*
    dwSpecial Ϊ���⸽���ֶ�
    ����            ��ʹ�غ�ʧ�ܣ�Ҳ�����Ѫ
*/
struct FGCard
{
    FGCard()
    {
        Reset();
    }

    void Reset()
    {
        nId = 0;
        byRevert = 0;
        bySuckBlood = 0;
        dwSpecial = 0;
        byPressAttack = 0;
        byCriticalStrike = 0;
        emType = emCardType_Null;
    }

    UINT nId;
    std::wstring strName;       ///> ������
    std::wstring strDecs;       ///> ��˵��
    emCardType emType;          ///> ������
    BYTE byRevert;              ///> �ظ�
    BYTE bySuckBlood;           ///> ��Ѫ
    DWORD dwSpecial;            ///> ���⸽��
    BYTE byPressAttack;         ///> ǿϮ
    BYTE byCriticalStrike;      ///> ����
};

struct FGGameInfo
{
    FGGameInfo()
    {
        iSeftLift = 0;
        iComputeLift = 0;
    }

    int iSeftLift;              ///> �Լ���Ѫ��
    int iComputeLift;           ///> ���Ե�Ѫ��
};

struct FGFightInfo
{
    FGFightInfo()
    {
        iSeftDamage = 0;
        iComputeDamage = 0;
        iSelfOutCard = 0;
        iComputeOutCard = 0;
    }

    int iSelfOutCard;           ///> �Լ����Ƶ�����
    int iComputeOutCard;        ///> ���Գ��Ƶ�����
    int iSeftDamage;            ///> �Լ�ս��
    int iComputeDamage;         ///> ����ս��
    FGCard outSelfCard;         ///> �Լ��ĳ���
    FGCard outComputeCard;      ///> ���Եĳ���
    FGGameInfo GameInfo;        ///> ��Ϸ��Ϣ
};

typedef std::vector<FGCard> VECFGCARD;
typedef std::vector<FGCard>::iterator VECFGCARDIT;
typedef std::vector<FGCard>::const_iterator VECFGCARDCONSTIT;
#endif