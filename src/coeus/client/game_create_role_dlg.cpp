#include "stdafx.h"
#include "game_create_role_dlg.h"

#define WINDOW_MAX_WIDTH            460
#define WINDOW_MAX_HEIGHT           465

#define WINDOW_MIN_WIDTH            460
#define WINDOW_MIN_HEIGHT           55

#define TIMER_BUTTON_MOVE           1

#define NUM_BUFFER_MAX              260

LRESULT GameCreateRoleDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
    m_NickNameEdit.Create( 
        GetViewHWND(), NULL, NULL, 
        WS_CHILD, 
        0, 4000, NULL);
    m_NickNameEdit.SetBgColor(RGB(255,255,255));
    m_NickNameEdit.SetColor(RGB(0,0,0));
    m_NickNameEdit.SetNotify(m_hWnd);

    OnSelectHuntsmanMan();
    return TRUE;
}

void GameCreateRoleDlg::OnClose()
{
    EndDialog(IDCLOSE);
}

void GameCreateRoleDlg::OnSysCommand(UINT nID, CPoint point)
{
    SetMsgHandled(FALSE);

    if (nID == SC_CLOSE)
    {
        EndDialog(IDCLOSE);
    }
}

void GameCreateRoleDlg::OnTimer(UINT_PTR nIDEvent)
{
}

void GameCreateRoleDlg::OnBtnClose()
{
    EndDialog(IDCLOSE);
}

LRESULT GameCreateRoleDlg::OnRoleResult(UINT uMsg,
    WPARAM wParam,
    LPARAM lParam,
    BOOL& bHandled)
{
    return TRUE;
}

void GameCreateRoleDlg::OnSelectHuntsmanMan()
{
    SelectRole(ID_SELECT_HUNTSMAN_MAN_BTN, ID_ROLE_IMG, "img_role_huntsman_man");
    SetItemText(ID_ROLE_NAME, L"��������");
    SetItemText(ID_ROLE_EXPLAIN, L"���������������ռ���Ȼ���и����ܷ����ʯͷ");
    SetItemVisible(ID_ROLE_EXPLAIN_DLG, TRUE);
}

void GameCreateRoleDlg::OnSelectHuntsmanWoMan()
{
    SelectRole(ID_SELECT_HUNTSMAN_WOMAN_BTN, ID_ROLE_IMG, "img_role_huntsman_woman");
    SetItemText(ID_ROLE_NAME, L"��������");
    SetItemText(ID_ROLE_EXPLAIN, L"���������������ռ���Ȼ���и����ܷ����ʯͷ");
    SetItemVisible(ID_ROLE_EXPLAIN_DLG, TRUE);
}

void GameCreateRoleDlg::OnSelectMechanicianMan()
{
    SelectRole(ID_SELECT_MECHANICIAN_MAN_BTN, ID_ROLE_IMG, "img_role_mechanician_man");
    SetItemText(ID_ROLE_NAME, L"��еʦ");
    SetItemText(ID_ROLE_EXPLAIN, L"���ȵķ����ң���е���찮���ߣ����Ƚ��ļ����ͳ��ߵ���������������");
    SetItemVisible(ID_ROLE_EXPLAIN_DLG, TRUE);
}

void GameCreateRoleDlg::OnSelectMechanicianWoMan()
{
    SelectRole(ID_SELECT_MECHANICIAN_WOMAN_BTN, ID_ROLE_IMG, "img_role_mechanician_woman");
    SetItemText(ID_ROLE_NAME, L"��еʦ");
    SetItemText(ID_ROLE_EXPLAIN, L"���ȵķ����ң���е���찮���ߣ����Ƚ��ļ����ͳ��ߵ���������������");
    SetItemVisible(ID_ROLE_EXPLAIN_DLG, TRUE);
}

void GameCreateRoleDlg::SelectRole(UINT nBtnId, UINT nImgId, const CStringA& csSkinName)
{
    SetItemAttribute(nBtnId, "sub", "4");
    SetItemAttribute(nImgId, "skin", csSkinName);
}

void GameCreateRoleDlg::OnBtnOK()
{
    EndDialog(IDOK);
}
