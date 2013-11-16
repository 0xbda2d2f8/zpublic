#ifndef __GAME_FG_BOARD_GAME
#define __GAME_FG_BOARD_GAME

#include "fg_player.h"

class CFGGame
{
public:
    CFGGame();

    ~CFGGame();

    BOOL Initialize();

    BOOL Unitialize();

    BOOL OutCard(UINT nIndex);

    BOOL GetCardList(VECFGCARD& vecCard);

    int GetSelfLift() const;

    int GetComputeyLift() const;

    int GetSelfDamageLift() const;

    int GetComputeDamageLift() const;

    const FGCard& GetOutComputeyCard() const;

    const FGCard& GetOutSelfCard() const;

private:
    BOOL _DealCard(UINT nNum);

private:
    CFGPlayer m_PlayerSelf;                         ///> �Լ�
    CFGPlayer m_PlayerComputer;                     ///> ����
    int m_iSelfDamageLift;                          ///> ս��
    int m_iComputeDamageLift;                       ///> ս��
    FGCard m_OutComputeyCard;                       ///> ���Եĳ���
    FGCard m_OutSelfCard;                           ///> �Լ��ĳ���
};

#endif