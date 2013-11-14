#ifndef __GAME_FG_BOARD_OBJECT_
#define __GAME_FG_BOARD_OBJECT_

#include "fg_iboard.h"

/*
    dwSpecial Ϊ���⸽���ֶ�
    ����            ��ʹ�غ�ʧ�ܣ�Ҳ�����Ѫ
*/

struct FGBoard
{
    FGBoard()
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
        emBoardType = emBoardType_Null;
    }

public:
    void Fight(
        const FGBoard& p1Card,     ///> ���1������
        const FGBoard& p2Card,     ///> ���2������
        int& p1Blood,               ///> ս�������1��Ѫ���仯 ����Ϊ��Ѫ ����Ϊ��Ѫ)
        int& p2Blood                ///> ս�������2��Ѫ���仯
        )
    {
        assert(p1Card.emBoardType != emBoardType_Null);
        assert(p2Card.emBoardType != emBoardType_Null);

        ///> �ظ�������һ����Ѫ��
        p1Blood = p1Card.byRevert;
        p2Blood = p2Card.byRevert;

        ///> ƽ��
        if (p1Card.emBoardType == p2Card.emBoardType)
        {
            return;
        }

        if (   (p1Card.emBoardType == emBoardType_Cloth && p2Card.emBoardType == emBoardType_Stone)
            || (p1Card.emBoardType == emBoardType_Stone && p2Card.emBoardType == emBoardType_Scissor)
            || (p1Card.emBoardType == emBoardType_Scissor && p2Card.emBoardType == emBoardType_Cloth) )
        {
            ///> ���1ʤ��
            _FightCalculate(p1Card, p2Card, p1Blood, p2Blood);
        }
        else
        {
            ///> ���2ʤ��
            _FightCalculate(p2Card, p1Card, p2Blood, p1Blood);
        }
    }

    void GenerateCard(FGBoard& card)
    {
        card.Reset();

        switch (rand() % 3)
        {
        case 0:
            card.emBoardType = emBoardType_Cloth;
            break;
        case 1:
            card.emBoardType = emBoardType_Scissor;
            break;
        case 2:
            card.emBoardType = emBoardType_Stone;
            break;
        }

        ///> 10%��������
        if (rand() % 10 == 0)
            card.dwSpecial &= 1;

        ///> 0 1 2 ���Եļ��ʷֱ�Ϊ 50% 30% 20%
        int n = rand() % 10;
        if (n < 2)
            card.byRevert = 2;
        else if (n < 5)
            card.byRevert = 1;
        n = rand() % 10;
        if (n < 2)
            card.byPressAttack = 2;
        else if (n < 5)
            card.byPressAttack = 1;

        ///> 0 1 2 3 ���Եļ��ʷֱ�Ϊ 50% 20% 20% 10%
        n = rand() % 10;
        if (n < 1)
            card.bySuckBlood = 3;
        else if (n < 3)
            card.bySuckBlood = 2;
        else if (n < 5)
            card.bySuckBlood = 1;
        n = rand() % 10;
        if (n < 1)
            card.byCriticalStrike = 3;
        else if (n < 3)
            card.byCriticalStrike = 2;
        else if (n < 5)
            card.byCriticalStrike = 1;
    }

private:
    void _FightCalculate(
        const FGBoard& WinnerCard,
        const FGBoard& LoserCard,
        int& WinnerBlood,
        int& LoserBlood )
    {
        if ((LoserCard.dwSpecial & 1) != 0)
        {
            ///> �������
            return;
        }
        else
        {
            ///> Ӯ����ѪЧ��
            WinnerBlood += WinnerCard.bySuckBlood;
            ///> ���-1Ѫ ���ǿϮЧ��
            LoserBlood -= 1 + WinnerCard.byPressAttack;
            ///> 50%���ʱ���Ч��
            if (WinnerCard.byCriticalStrike && (rand() % 2) == 0)
            {
                LoserBlood -= WinnerCard.byCriticalStrike;
            }
        }
    }

    emBoardType emBoardType;    ///> ������
    BYTE byRevert;              ///> �ظ�
    BYTE bySuckBlood;           ///> ��Ѫ
    DWORD dwSpecial;            ///> ���⸽��
    BYTE byPressAttack;         ///> ǿϮ
    BYTE byCriticalStrike;      ///> ����
};

#endif