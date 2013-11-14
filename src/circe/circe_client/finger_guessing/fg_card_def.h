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
        byRevert = 0;
        bySuckBlood = 0;
        dwSpecial = 0;
        byPressAttack = 0;
        byCriticalStrike = 0;
        emType = emCardType_Null;
    }

    emCardType emType;    ///> ������
    BYTE byRevert;              ///> �ظ�
    BYTE bySuckBlood;           ///> ��Ѫ
    DWORD dwSpecial;            ///> ���⸽��
    BYTE byPressAttack;         ///> ǿϮ
    BYTE byCriticalStrike;      ///> ����
};

typedef std::vector<FGCard> vecFGCard;
typedef std::vector<FGCard>::iterator vecFGCardIt;
typedef std::vector<FGCard>::const_iterator vecFGCardConstIt;
#endif