#ifndef __GAME_FG_BOARD_GAME
#define __GAME_FG_BOARD_GAME

#include "fg_board_game_def.h"

class CFGBoardGame
{
public:
    CFGBoardGame();

    ~CFGBoardGame();

    BOOL Push(CFGPlayerGame* fgPlayerGame);

    BOOL Pop(UINT nIndex);

    BOOL DealBoard(UINT nIndex);

private:
    vecFGPlayerGame m_vecPlayerGame;                ///> ����б�
};

#endif