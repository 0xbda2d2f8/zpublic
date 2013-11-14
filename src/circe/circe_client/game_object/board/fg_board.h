#ifndef __GAME_FG_BOARD_OBJECT_
#define __GAME_FG_BOARD_OBJECT_

#include "fg_iboard.h"

/*
    dwSpecial Ϊ���⸽���ֶ�
    ����            ��ʹ�غ�ʧ�ܣ�Ҳ�����Ѫ
*/

struct CFGBoard
{
    CFGBoard()
    {
        byRevert = 0;
        bySuckBlood = 0;
        dwSpecial = 0;
        byPressAttack = 0;
        byCriticalStrike = 0;
        emBoardType = emBoardType_Null;
    }

    emBoardType emBoardType;    ///> ������
    BYTE byRevert;              ///> �ظ�
    BYTE bySuckBlood;           ///> ��Ѫ
    DWORD dwSpecial;            ///> ���⸽��
    BYTE byPressAttack;         ///> ǿϮ
    BYTE byCriticalStrike;      ///> ����
};

#endif