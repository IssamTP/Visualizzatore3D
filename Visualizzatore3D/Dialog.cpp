#include "stdafx.h"
#include "Dialog.h"

CDialog::CDialog(HINSTANCE istanza, UINT idNomeFinestra, int idRisorsaTemplate)
	: CWindow(istanza, idNomeFinestra, nullptr)
{
	m_IdRisorsaTemplate = idRisorsaTemplate;
}

CDialog::~CDialog()
{
	for (auto controllo = m_ControlliFinestra.begin(); controllo != m_ControlliFinestra.end(); controllo++)
		delete controllo->second;
	m_ControlliFinestra.clear();
}

void CDialog::CreaDialog(HWND parent)
{
	m_HandleFinestra = CreateDialogParam(m_Istanza, MAKEINTRESOURCE(m_IdRisorsaTemplate), parent, &CDialog::DlgProc, reinterpret_cast<LPARAM>(this));
	CreaControlliDaRisorse();
}

void CDialog::MostraFinestra(int comandoShow)
{
	ShowWindow(m_HandleFinestra, comandoShow);
}

INT_PTR CDialog::ProceduraDialog(HWND hWnd, UINT messaggio, WPARAM wParam, LPARAM lParam)
{
	INT_PTR messaggioGestito = FALSE;
	switch (messaggio)
	{
	case WM_CREATE:
	default:
		messaggioGestito = DefDlgProc(hWnd, messaggio, wParam, lParam);
		break;
	case WM_VSCROLL:
		OnVScroll(wParam, lParam);
		break;
	case WM_HSCROLL:
		OnHScroll(wParam, lParam);
		break;
	case WM_CLOSE:
		messaggioGestito = TRUE;
		DestroyWindow(m_HandleFinestra);
		break;
	case WM_PAINT:
		OnPaint();
		break;
	case WM_DESTROY:
		messaggioGestito = TRUE;
		// TODO: Pulizia risorse...
		PostQuitMessage(EXIT_SUCCESS);
		break;
	case WM_NOTIFY:
		OnNotify(reinterpret_cast<LPNMHDR>(lParam));
		break;
	}
	return messaggioGestito;
}

INT_PTR CALLBACK CDialog::DlgProc(HWND hWnd, UINT messaggio, WPARAM wParam, LPARAM lParam)
{
	CDialog* dialogDiRiferimento;
	if (messaggio == WM_INITDIALOG)
	{
		dialogDiRiferimento = reinterpret_cast<CDialog *>(lParam);
		SetWindowLongPtr(hWnd, DWLP_USER, reinterpret_cast<LONG_PTR>(dialogDiRiferimento));
	}
	else
		dialogDiRiferimento = reinterpret_cast<CDialog *>(GetWindowLongPtr(hWnd, DWLP_USER));
	if (dialogDiRiferimento != nullptr)
		// Now that we have recovered our "this" pointer, let the member function finish the job.
		return dialogDiRiferimento->ProceduraDialog(hWnd, messaggio, wParam, lParam);
	else
		return FALSE;
}
