#include "stdafx.h"
#include "resource.h"

#include "World3Dlg.h"

CWorld3Dlg::CWorld3Dlg()
{
    m_iSeftLift = 0;
    m_iComputey = 0;
}

LRESULT CWorld3Dlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    CenterWindow(GetParent());
    m_SeftCardListBox.Attach(GetDlgItem(IDC_LIST1));
    m_FightInfoEdit.Attach(GetDlgItem(IDC_EDIT2));
    m_Game.Initialize();

    vecFGCard seftcard;
    CString csCard;
    CString csSeftLiftValue;
    CString csComputerLiftValue;

    m_Game.GetCardList(seftcard);

    for (UINT n = 0; n < seftcard.size(); ++n)
    {
        _ConvertCardToStirng(seftcard[n], csCard);
        m_SeftCardListBox.AddString(csCard);
    }

    csSeftLiftValue.Format(L"%d", m_Game.GetSeftLift());
    csComputerLiftValue.Format(L"%d", m_Game.GetComputeyLift());
    SetDlgItemText(IDC_STATIC7, csSeftLiftValue);
    SetDlgItemText(IDC_STATIC6, csComputerLiftValue);
    return TRUE;
}

LRESULT CWorld3Dlg::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    EndDialog(0);
    return 0;
}

LRESULT CWorld3Dlg::OnBnClickedOk(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    vecFGCard seftcard;
    FGCard outComputeyCard;
    CString csCard;
    CString csSeftLiftValue;
    CString csComputerLiftValue;
    CString csComputeyCard;
    CString csFightInfo;

    int nListCurSel = m_SeftCardListBox.GetCurSel();
    m_SeftCardListBox.DeleteString(nListCurSel);
    m_Game.OutCard(nListCurSel);
    m_Game.GetCardList(seftcard);

    if (seftcard.size() < nListCurSel)
    {
        return FALSE;
    }

    _ConvertCardToStirng(seftcard[nListCurSel], csCard);
    m_SeftCardListBox.AddString(csCard);
    m_FightInfoEdit.GetWindowText(csFightInfo);

    if (!csFightInfo.IsEmpty())
    {
        csFightInfo += _T("\r\n");
    }

    outComputeyCard = m_Game.GetOutComputeyCard();

    _ConvertCardToStirng(outComputeyCard, csComputeyCard);

    csFightInfo.AppendFormat(L"�Է����: %s, ��ʧ����ֵ:%d ",
        csComputeyCard,
        m_Game.GetBattleDamageLift());

    csSeftLiftValue.Format(L"%d", m_Game.GetSeftLift());
    m_FightInfoEdit.SetWindowText(csFightInfo);

    csSeftLiftValue.Format(L"%d", m_Game.GetSeftLift());
    csComputerLiftValue.Format(L"%d", m_Game.GetComputeyLift());
    SetDlgItemText(IDC_STATIC7, csSeftLiftValue);
    SetDlgItemText(IDC_STATIC6, csComputerLiftValue);
    return 0;
}

void CWorld3Dlg::_ConvertCardToStirng(const FGCard& card, CString& csConvertString)
{
    CString cardType;
    switch (card.emType)
    {
    case emCardType_Scissor:
        cardType = L"����";
        break;
    case emCardType_Stone:
        cardType = L"ʯͷ";
        break;
    case emCardType_Cloth:
        cardType = L"��    ";
        break;
    default:
        break;
    }

    csConvertString.Format(L"%s  �ظ�ֵ:%d, ��Ѫֵ:%d, ����:%d, ǿϮ:%d, ����:%d",
        cardType,
        card.byRevert,
        card.bySuckBlood,
        card.dwSpecial,
        card.byPressAttack,
        card.byCriticalStrike);
}
