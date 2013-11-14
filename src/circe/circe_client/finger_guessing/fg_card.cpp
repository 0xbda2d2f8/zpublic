#include "stdafx.h"
#include "fg_card.h"

void _FightCalculate(
    const FGCard& WinnerCard,
    const FGCard& LoserCard,
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

void Fight(
    const FGCard& p1Card, /*/> ���1������ */
    const FGCard& p2Card, /*/> ���2������ */
    int& p1Blood, /*/> ս?�����1��Ѫ���� ?����Ϊ��Ѫ ����Ϊ��Ѫ) */
    int& p2Blood /*/> ս?�����2��Ѫ���� ?*/ )
{
    assert(p1Card.emType != emCardType_Null);
    assert(p2Card.emType != emCardType_Null);

    ///> �ظ�������һ����Ѫ��
    p1Blood = p1Card.byRevert;
    p2Blood = p2Card.byRevert;

    ///> ƽ��
    if (p1Card.emType == p2Card.emType)
    {
        return;
    }

    if (   (p1Card.emType == emCardType_Cloth && p2Card.emType == emCardType_Stone)
        || (p1Card.emType == emCardType_Stone && p2Card.emType == emCardType_Scissor)
        || (p1Card.emType == emCardType_Scissor && p2Card.emType == emCardType_Cloth) )
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

void GenerateCard( FGCard& card )
{
    card.Reset();

    switch (rand() % 3)
    {
    case 0:
        card.emType = emCardType_Cloth;
        break;
    case 1:
        card.emType = emCardType_Scissor;
        break;
    case 2:
        card.emType = emCardType_Stone;
        break;
    }

    ///> 10%��������
    if (rand() % 10 == 0)
        card.dwSpecial &= 1;

    ///> 10%���ʻظ�1
    if (rand() % 10 == 0)
        card.byRevert = 1;

    ///> ǿϮ���� 0 1 2 Ϊ 50% 30% 20%
    int n = rand() % 10;
    if (n < 2)
        card.byPressAttack = 2;
    else if (n < 5)
        card.byPressAttack = 1;

    ///> ��Ѫ0 1 2���ʷֱ� 80 10 10
    n = rand() % 10;
    if (n < 1)
        card.bySuckBlood = 1;
    else if (n < 2)
        card.bySuckBlood = 2;

    ///> 0 1 2 3 ���Եļ��ʷֱ�Ϊ 50% 20% 20% 10%
    n = rand() % 10;
    if (n < 1)
        card.byCriticalStrike = 3;
    else if (n < 3)
        card.byCriticalStrike = 2;
    else if (n < 5)
        card.byCriticalStrike = 1;
}
