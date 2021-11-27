#include "stdafx.h"
#include "Dialog.h"

#pragma region Costruttori

CDialog::CDialog(HINSTANCE istanza, UINT idNomeFinestra, int idRisorsaTemplate)
	: CWindow(istanza, idNomeFinestra, nullptr)
{
	m_RisultatoRegistrazione = 1;
	m_IdRisorsaTemplate = idRisorsaTemplate;
}

CDialog::~CDialog()
{
	for (auto controllo = m_ControlliFinestra.begin(); controllo != m_ControlliFinestra.end(); controllo++)
		delete controllo->second;
	m_ControlliFinestra.clear();
}

#pragma endregion

#pragma region Wrap API Comuni

/// <summary>
/// Implementazione specifica per la dialog.
/// </summary>
/// <param name="parent"></param>
void CDialog::CreaFinestra(HWND parent)
{
	m_HandleProprietario = parent;
	m_HandleFinestra = CreateDialogParam(m_Istanza, MAKEINTRESOURCE(m_IdRisorsaTemplate), parent, &CDialog::DlgProc, reinterpret_cast<LPARAM>(this));
	CreaControlliDaRisorse();
}

#pragma endregion

#pragma region Gestione Eventi

#pragma endregion

INT_PTR CDialog::ProceduraDialog(HWND hWnd, UINT messaggio, WPARAM wParam, LPARAM lParam)
{
	INT_PTR messaggioGestito = FALSE;
	switch (messaggio)
	{
	default:
		//messaggioGestito = DefDlgProc(hWnd, messaggio, wParam, lParam);
		break;
	case WM_CLOSE:
	{
		messaggioGestito = TRUE;
		OnClose();
		DestroyWindow(m_HandleFinestra);
	}
		break;
	case WM_DESTROY:
	{
		messaggioGestito = TRUE;
		PostQuitMessage(EXIT_SUCCESS);
	}
		break;
	case WM_HSCROLL:
	{
		OnHScroll(LOWORD(wParam), HIWORD(wParam), reinterpret_cast<HANDLE>(lParam));
		messaggioGestito = TRUE;
	}
		break;
	case WM_INITDIALOG:
	{
		m_HandleFinestra = hWnd;
		CentraFinestra();
		messaggioGestito = TRUE;
	}
		break;
	case WM_PAINT:
	{
		OnPaint();
		messaggioGestito = TRUE;
	}
		break;
	case WM_VSCROLL:
	{
		OnVScroll(LOWORD(wParam), HIWORD(wParam), reinterpret_cast<HANDLE>(lParam));
		messaggioGestito = TRUE;
	}
		break;
	case WM_NOTIFY:
	{
		OnNotify(LOWORD(wParam), reinterpret_cast<LPNMHDR>(lParam));
		messaggioGestito = TRUE;
	}
		break;
	}
	return messaggioGestito;
}

/// <summary>
/// Sostituisce l'altra procedura, quindi...
/// </summary>
/// <param name="hWnd"></param>
/// <param name="messaggio"></param>
/// <param name="wParam"></param>
/// <param name="lParam"></param>
/// <returns></returns>
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
