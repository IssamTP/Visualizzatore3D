#include "stdafx.h"
#include "Visualizzatore3D.h"
#include "Visualizzatore3DDlg.h"

CVisualizzatore3DDlg::CVisualizzatore3DDlg(HINSTANCE istanza, int idRisorsa)
	: CDialog(istanza, IDC_VISUALIZZATORE3D, idRisorsa)
{
	m_Segnaposto = nullptr;
	m_HSlider = nullptr;
	m_Texture = nullptr;
	m_VSlider = nullptr;
	m_pOgre = nullptr;
}

CVisualizzatore3DDlg::~CVisualizzatore3DDlg()
{
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

	controllo = m_ControlliFinestra.insert(m_ControlliFinestra.end(), std::make_pair(IDC_SEGNAPOSTO_OGRE, new CWindow()));
	controllo->second->SetHandleFinestra(GetDlgItem(m_HandleFinestra, IDC_SEGNAPOSTO_OGRE));
	m_Segnaposto = reinterpret_cast<CWindow*>(controllo->second);
}

void CVisualizzatore3DDlg::CreaDialog(HWND parent)
{
	CDialog::CreaDialog(parent);
	CreaControlloOgre();
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
		case TB_THUMBPOSITION: // The trackbar received WM_LBUTTONUP following a TB_THUMBTRACK notification code.
		case TB_THUMBTRACK: // The user dragged the slider.
			posizione = HIWORD(wParam);
			if (m_pOgre != nullptr)
				m_pOgre->ImpostaRotazione(posizione - 180, 0u);
			SetDlgItemText(m_HandleFinestra, IDC_HROT, std::to_wstring(posizione).append(L"°").c_str());
			break;
		case TB_TOP: // The user pressed the HOME key(VK_HOME).
			break;
		};
	}
}

void CVisualizzatore3DDlg::OnNotify(HWND hWnd, UINT messaggio, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDC_LIST1:
		if (m_Texture != nullptr)
		{
			NMHDR* pNMHDR = reinterpret_cast<NMHDR*>(lParam);
			switch (pNMHDR->code)
			{
			case NM_CLICK:
				NMITEMACTIVATE* pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
				if (0 <= pNMItemActivate->iItem)
				{
					LVITEM elemento;
					memset(&elemento, 0, sizeof(LVITEM));
					elemento.iItem = pNMItemActivate->iItem;
					m_Texture->GetElemento(elemento);
					std::wstring nomeMateriale(elemento.pszText);
					m_pOgre->ImpostaMateriale(Ogre::String(nomeMateriale.begin(), nomeMateriale.end()));
				}
				break;
			}
		}
		break;
	}
}

void CVisualizzatore3DDlg::OnVScroll(WPARAM wParam, LPARAM lParam)
{
	int posizione;
	if (m_VSlider != nullptr)
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
			if (m_pOgre != nullptr)
				m_pOgre->ImpostaRotazione(posizione - 180, 1);
			SetDlgItemText(m_HandleFinestra, IDC_HROT, std::to_wstring(posizione).append(L"°").c_str());
			break;
		case TB_TOP: // The user pressed the HOME key(VK_HOME).
			break;
		};
	}
}

void CVisualizzatore3DDlg::CreaControlloOgre()
{
	RECT dimensioni;
	GetWindowRect(m_Segnaposto->HandleFinestra(), &dimensioni);
	m_pOgre = new COgreCtrl();
	m_pOgre->InizializzaControllo(m_Segnaposto->HandleFinestra(), dimensioni);
	std::vector<std::wstring> elementiDaInserire;
	m_pOgre->GetNomiMateriali(elementiDaInserire);

	HIMAGELIST texture = ImageList_Create(48, 48, ILC_COLORDDB | ILC_ORIGINALSIZE, 5, 5);
	ImageList_Add(texture, (HBITMAP)LoadImage(m_Istanza, MAKEINTRESOURCE(IDB_WHITE), IMAGE_BITMAP, 48, 48, LR_DEFAULTCOLOR), nullptr);
	ImageList_Add(texture, (HBITMAP)LoadImage(m_Istanza, MAKEINTRESOURCE(IDB_WHITE2), IMAGE_BITMAP, 48, 48, LR_DEFAULTCOLOR), nullptr);
	ImageList_Add(texture, (HBITMAP)LoadImage(m_Istanza, MAKEINTRESOURCE(IDB_WHITE3), IMAGE_BITMAP, 48, 48, LR_DEFAULTCOLOR), nullptr);
s	ImageList_Add(texture, (HBITMAP)LoadImage(m_Istanza, MAKEINTRESOURCE(IDB_SPHEREMAP), IMAGE_BITMAP, 48, 48, LR_DEFAULTCOLOR), nullptr);
	ImageList_Add(texture, (HBITMAP)LoadImage(m_Istanza, MAKEINTRESOURCE(IDB_EYES), IMAGE_BITMAP, 48, 48, LR_DEFAULTCOLOR), nullptr);
	ImageList_Add(texture, (HBITMAP)LoadImage(m_Istanza, MAKEINTRESOURCE(IDB_GREENSKIN), IMAGE_BITMAP, 48, 48, LR_DEFAULTCOLOR), nullptr);
	ImageList_Add(texture, (HBITMAP)LoadImage(m_Istanza, MAKEINTRESOURCE(IDB_TUSK), IMAGE_BITMAP, 48, 48, LR_DEFAULTCOLOR), nullptr);
	m_Texture->SetImageList(texture);

	bool selezionato = true;
	int indice = 0;
	for (auto materiale = elementiDaInserire.begin(); materiale != elementiDaInserire.end(); materiale++)
	{
		m_Texture->AggiungiElemento(materiale->c_str(), indice++, selezionato);
		selezionato = false;
	}
	m_ControlliFinestra.insert(m_ControlliFinestra.end(), std::make_pair(IDC_CONTROLLO_OGRE, m_pOgre));
}