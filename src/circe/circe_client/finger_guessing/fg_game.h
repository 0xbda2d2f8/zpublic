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

    int GetSeftLift() const;

    int GetComputeyLift() const;

    int GetBattleDamageLift() const;

    const FGCard& GetOutComputeyCard() const;

private:
    BOOL _DealCard(UINT nNum);

private:
    CFGPlayer m_PlayerSeft;                         ///> �Լ�
    CFGPlayer m_PlayerComputer;                     ///> ����
    int m_iBattleDamageLift;                        ///> ս��
    FGCard m_OutComputeyCard;                       ///> ���Եĳ���
};

#endif