#include "framework.h"
#include "Visualizzatore3D.h"
#include "Visualizzatore3DDlg.h"

CVisualizzatore3DDlg::CVisualizzatore3DDlg(HINSTANCE istanza, int idRisorsa)
	: CDialog(istanza, idRisorsa)
{
	m_HSlider = nullptr;
	m_Texture = nullptr;
	m_VSlider = nullptr;
}

void CVisualizzatore3DDlg::CreaControlliDaRisorse()
{
	auto controllo = m_ControlliFinestra.insert(m_ControlliFinestra.end(), std::make_pair(IDC_SLIDER1, new CSliderCtrl()));
	controllo->second->SetHandleFinestra(GetDlgItem(m_HandleFinestra, IDC_SLIDER1));
	m_VSlider = reinterpret_cast<CSliderCtrl *>(controllo->second);
	m_VSlider->SetIntervallo(0U, 360U);
	SetDlgItemText(m_HandleFinestra, IDC_VROT, TEXT("180°"));

	controllo = m_ControlliFinestra.insert(m_ControlliFinestra.end(), std::make_pair(IDC_SLIDER2, new CSliderCtrl()));
	controllo->second->SetHandleFinestra(GetDlgItem(m_HandleFinestra, IDC_SLIDER2));
	m_HSlider = reinterpret_cast<CSliderCtrl *>(controllo->second);
	m_HSlider->SetIntervallo(0u, 360U);
	SetDlgItemText(m_HandleFinestra, IDC_HROT, TEXT("180°"));

	controllo = m_ControlliFinestra.insert(m_ControlliFinestra.end(), std::make_pair(IDC_LIST1, new CListCtrl()));
	controllo->second->SetHandleFinestra(GetDlgItem(m_HandleFinestra, IDC_LIST1));
	m_Texture = reinterpret_cast<CListCtrl*>(controllo->second);
	m_Texture->AggiungiElemento(_T("Texture_1"), true);
}

void CVisualizzatore3DDlg::OnHScroll(WPARAM wParam, LPARAM lParam)
{
	int posizione;
	if (m_HSlider != nullptr)
	{
		switch (LOWORD(wParam))
		{
		case TB_BOTTOM: // The user pressed the END key(VK_END).
			break;
		case TB_ENDTRACK: // The trackbar received WM_KEYUP, meaning that the user released a key that sent a relevant virtual key code.
			break;
		case TB_LINEDOWN: // The user pressed the RIGHT ARROW(VK_RIGHT) or DOWN ARROW(VK_DOWN) key.
			break;
		case TB_LINEUP: // The user pressed the LEFT ARROW(VK_LEFT) or UP ARROW(VK_UP) key.
			break;
		case TB_PAGEDOWN: // The user clicked the channel below or to the right of the slider(VK_NEXT).
			break;
		case TB_PAGEUP: // The user clicked the channel above or to the left of the slider(VK_PRIOR).
			break;
		case  TB_THUMBPOSITION: // The trackbar received WM_LBUTTONUP following a TB_THUMBTRACK notification code.
		case TB_THUMBTRACK: // The user dragged the slider.
			posizione = HIWORD(wParam);
			SetDlgItemText(m_HandleFinestra, IDC_HROT, std::to_wstring(posizione).append(L"°").c_str());
			break;
		case TB_TOP: // The user pressed the HOME key(VK_HOME).
			break;
		};
	}
}

void CVisualizzatore3DDlg::OnNotify(LPNMHDR pNMHDR)
{
	if (m_Texture != nullptr)
	{
		switch (pNMHDR->code)
		{
		case LVN_GETDISPINFO:
			m_Texture->DisplayInfoNotification(reinterpret_cast<LV_DISPINFO*>(pNMHDR));
			break;
		}
	}

}

void CVisualizzatore3DDlg::OnVScroll(WPARAM wParam, LPARAM lParam)
{
	int posizione;
	if (m_HSlider != nullptr)
	{
		switch (LOWORD(wParam))
		{
		case TB_BOTTOM: // The user pressed the END key(VK_END).
			break;
		case TB_ENDTRACK: // The trackbar received WM_KEYUP, meaning that the user released a key that sent a relevant virtual key code.
			break;
		case TB_LINEDOWN: // The user pressed the RIGHT ARROW(VK_RIGHT) or DOWN ARROW(VK_DOWN) key.
			break;
		case TB_LINEUP: // The user pressed the LEFT ARROW(VK_LEFT) or UP ARROW(VK_UP) key.
			break;
		case TB_PAGEDOWN: // The user clicked the channel below or to the right of the slider(VK_NEXT).
			break;
		case TB_PAGEUP: // The user clicked the channel above or to the left of the slider(VK_PRIOR).
			break;
		case  TB_THUMBPOSITION: // The trackbar received WM_LBUTTONUP following a TB_THUMBTRACK notification code.
		case TB_THUMBTRACK: // The user dragged the slider.
			posizione = HIWORD(wParam);
			SetDlgItemText(m_HandleFinestra, IDC_VROT, std::to_wstring(posizione).append(L"°").c_str());
			break;
		case TB_TOP: // The user pressed the HOME key(VK_HOME).
			break;
		};
	}
}