#include "framework.h"
#include "Dialog.h"

CDialog* g_Finestra = nullptr;

INT_PTR CALLBACK ProceduraDialog(HWND hWnd, UINT messaggio, WPARAM wParam, LPARAM lParam)
{
	INT_PTR messaggioGestito = FALSE;
	switch (messaggio)
	{
	default:
		messaggioGestito = DefWindowProc(hWnd, messaggio, wParam, lParam);
		break;
	case WM_CREATE:
		break;
	case WM_VSCROLL:
		g_Finestra->OnVScroll(wParam, lParam);
		break;
	case WM_HSCROLL:
		g_Finestra->OnHScroll(wParam, lParam);
		break;
	case WM_CLOSE:
		messaggioGestito = TRUE;
		DestroyWindow(g_Finestra->m_HandleFinestra);
		break;
	case WM_PAINT:
		g_Finestra->OnPaint();
		break;
	case WM_DESTROY:
		messaggioGestito = TRUE;
		// TODO: Pulizia risorse...
		PostQuitMessage(EXIT_SUCCESS);
		break;
	case WM_NOTIFY:
		g_Finestra->OnNotify(reinterpret_cast<LPNMHDR>(lParam));
		break;
	}
	return messaggioGestito;
}

CDialog::CDialog(HINSTANCE istanza, int idRisorsaTemplate)
{
	m_HandleFinestra = nullptr;
	m_IdRisorsaTemplate = idRisorsaTemplate;
	m_Istanza = istanza;
	g_Finestra = this;
}

CDialog::~CDialog()
{
	for (auto controllo = m_ControlliFinestra.begin(); controllo != m_ControlliFinestra.end(); controllo++)
		delete controllo->second;
	m_ControlliFinestra.clear();
}

void CDialog::CreaDialog(HWND parent)
{
	m_HandleFinestra = CreateDialogParam(m_Istanza, MAKEINTRESOURCE(m_IdRisorsaTemplate), parent, ProceduraDialog, 0UL);
	CreaControlliDaRisorse();
}

void CDialog::MostraFinestra(int comandoShow)
{
	ShowWindow(m_HandleFinestra, comandoShow);
}

