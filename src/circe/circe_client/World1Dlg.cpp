#include "stdafx.h"
#include "resource.h"

#include "World1Dlg.h"

LRESULT CWorld1Dlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    m_nMoney = 100;
    CenterWindow(GetParent());
    return TRUE;
}

LRESULT CWorld1Dlg::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    EndDialog(0);
    return 0;
}

LRESULT CWorld1Dlg::OnBnClickedW1Zhiliao(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    if (m_nMoney > 0)
    {
        MessageBox(L"ҩ����ͣ��");
        m_nMoney -= 20;
        CString strText;
        strText.Format(L"��%d", m_nMoney);
        SetDlgItemText(IDC_W1_MONEY, strText);
    }
    else
    {
        MessageBox(L"ûǮ�ˣ����ֵ��");
    }
    return 0;
}
