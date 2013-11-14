#ifndef __GAME_FG_BOARD_OBJECT_
#define __GAME_FG_BOARD_OBJECT_

#include "fg_card_def.h"

void Fight(
    const FGCard& p1Card,     ///> ���1������
    const FGCard& p2Card,     ///> ���2������
    int& p1Blood,               ///> ս�������1��Ѫ���仯 ����Ϊ��Ѫ ����Ϊ��Ѫ)
    int& p2Blood                ///> ս�������2��Ѫ���仯
    );

void GenerateCard(FGCard& card);

#endif