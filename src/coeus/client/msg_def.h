#pragma once

enum emUserMsg
{
    msg_login_result        = WM_USER + 2000,       ///> ��½���
    msg_register_result,                            ///> ע����
    msg_create_role_result,                         ///> ���Ž��
    msg_get_rand_name_result,                       ///> ����ǳƽ��
    msg_check_nickname_result,                      ///> ����ǳƿ��ý��
    msg_goto_world,                                 ///>
    msg_player_info,
    msg_traymessage,                                ///> ������Ϣ
    msg_game_quit,                                  ///> �˳���Ϸ
};
