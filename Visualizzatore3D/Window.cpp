#include "stdafx.h"
#include "Visualizzatore3D.h"
#include "Window.h"

#pragma region Costruttori

CWindow::CWindow()
{
	m_RisultatoRegistrazione = 0;
	m_DisegnoAutonomo = false;
	m_IconaFinestra = nullptr;
	m_Istanza = nullptr;
	m_HandleProprietario = nullptr;
	m_HandleFinestra = nullptr;
	memset(&m_InformazioniFinestra, 0, sizeof(WNDCLASSEX));
	m_InformazioniFinestra.cbSize = sizeof(WNDCLASSEX);
}

/// <summary>
/// Utile per la derivazione da CDialog.
/// </summary>
/// <param name="istanza"></param>
/// <param name="idRisorsaNomeFinestra"></param>
/// <param name="proprietaria"></param>
CWindow::CWindow(HINSTANCE istanza, UINT idRisorsaNomeFinestra, HWND proprietaria)
	: CWindow()
{
	TCHAR buffer[C_NUMERO_MASSIMO_CARATTERI];
	m_HandleProprietario = proprietaria;
	m_Istanza = istanza;
	if (LoadString(m_Istanza, idRisorsaNomeFinestra, buffer, C_NUMERO_MASSIMO_CARATTERI) > 0)
		m_TitoloFinestra = std::wstring(buffer);
	else
		MostraMessaggioDiErrore();
}

/// <summary>
/// Crea una finestra vera e propria.
/// </summary>
/// <param name="istanza"></param>
/// <param name="idRisorsaNomeClasse"></param>
/// <param name="idRisorsaNomeFinestra"></param>
/// <param name="proprietaria"></param>
CWindow::CWindow(HINSTANCE istanza, UINT idRisorsaNomeClasse, UINT idRisorsaNomeFinestra, HWND proprietaria)
	: CWindow(istanza, idRisorsaNomeFinestra, proprietaria)
{
	TCHAR buffer[C_NUMERO_MASSIMO_CARATTERI];
	if (LoadString(m_Istanza, idRisorsaNomeClasse, buffer, C_NUMERO_MASSIMO_CARATTERI) > 0)
		m_NomeClasseFinestra = std::wstring(buffer);
	else
		MostraMessaggioDiErrore();
}

#pragma endregion

/// <summary>
/// Mette la finestra al centro dello schermo.
/// </summary>
void CWindow::CentraFinestra()
{
	int larghezzaSchermo, altezzaSchermo;
	RECT dimensioniFinestra;
	larghezzaSchermo = GetSystemMetrics(SM_CXSCREEN);
	altezzaSchermo = GetSystemMetrics(SM_CYSCREEN);
	GetWindowRect(m_HandleFinestra, &dimensioniFinestra);
	MoveWindow(m_HandleFinestra, (larghezzaSchermo - (dimensioniFinestra.right - dimensioniFinestra.left)) / 2, (altezzaSchermo - (dimensioniFinestra.bottom - dimensioniFinestra.top)) / 2, dimensioniFinestra.right - dimensioniFinestra.left, dimensioniFinestra.bottom - dimensioniFinestra.top, TRUE);
}

void CWindow::MostraMessaggioDiErrore()
{
	DWORD ultimoErrore = GetLastError();
	DWORD specifiche = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
	LPTSTR messaggio = nullptr;
	FormatMessage(specifiche, nullptr, ultimoErrore, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), messaggio, 1024, nullptr);
	MessageBox(m_HandleFinestra, messaggio, _T("Messaggio di Sistema"), MB_OK | MB_ICONERROR);
	LocalFree(messaggio);
}

LONG CWindow::AltezzaFinestra() const
{
	RECT rettangoloFinestra;
	GetWindowRect(m_HandleFinestra, &rettangoloFinestra);
	return rettangoloFinestra.bottom - rettangoloFinestra.top;
}

LONG CWindow::LarghezzaFinestra() const
{
	RECT rettangoloFinestra;
	GetWindowRect(m_HandleFinestra, &rettangoloFinestra);
	return rettangoloFinestra.right - rettangoloFinestra.left;
}

#pragma region Wrap API Comuni

/// <summary>
/// Invalida l'intera finestra. Il messaggio non viene accodato.
/// </summary>
void CWindow::AggiornaFinestra()
{
	UpdateWindow(m_HandleFinestra);
}

/// <summary>
/// Crea materialmente la finestra.
/// </summary>
void CWindow::CreaFinestra(HWND parent)
{
	if (m_RisultatoRegistrazione != 0)
	{
		DWORD stileFinestra = 0UL;
		DWORD stileFinestraEsteso = 0UL;

		m_HandleProprietario = parent;
		m_HandleFinestra = CreateWindowEx(stileFinestraEsteso, m_NomeClasseFinestra.c_str(), _T(""), stileFinestra, 640, 480, 640, 480, m_HandleProprietario, nullptr, m_Istanza, this);
	}
}

/// <summary>
/// Mostra la finestra nella modalità specificata.
/// </summary>
/// <param name="comandoShow"></param>
void CWindow::MostraFinestra(int comandoShow)
{
	ShowWindow(m_HandleFinestra, comandoShow);
}

/// <summary>
/// https://docs.microsoft.com/it-it/windows/win32/api/winuser/ns-winuser-wndclassexa/
/// Si noti che la funzione dovrebbe chiamare:
/// 1) SetIcon;
/// 2) SetCursor;
/// </summary>
/// <todo>Terminare l'implementazione.</todo>
void CWindow::RegistraClasseFinestra()
{
	// Esempio di registrazione:
	m_InformazioniFinestra.style = CS_HREDRAW | CS_VREDRAW;
	m_InformazioniFinestra.lpfnWndProc = &CWindow::WndProc;
	m_InformazioniFinestra.cbClsExtra = 0;
	m_InformazioniFinestra.cbWndExtra = 0;
	m_InformazioniFinestra.hInstance = m_Istanza;
	m_InformazioniFinestra.hIcon = static_cast<HICON>(m_IconaFinestra);
	m_InformazioniFinestra.hCursor = static_cast<HCURSOR>(m_Cursore);
	m_InformazioniFinestra.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	m_InformazioniFinestra.lpszMenuName = MAKEINTRESOURCEW(IDC_VISUALIZZATORE3D);
	m_InformazioniFinestra.lpszClassName = m_NomeClasseFinestra.c_str();
	m_InformazioniFinestra.hIconSm = LoadIcon(m_InformazioniFinestra.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	m_RisultatoRegistrazione = RegisterClassEx(&m_InformazioniFinestra);
}

/// <summary>
/// 
/// </summary>
/// <param name="idRisorsa"></param>
/// <param name="usaCaricamentoAvanzato"></param>
/// <todo>Caricamento cursorse personalizzato</todo>
void CWindow::SetCursor(UINT idRisorsa, bool usaCaricamentoAvanzato)
{
	if (usaCaricamentoAvanzato)
		m_Cursore = LoadImage(m_Istanza, MAKEINTRESOURCE(idRisorsa), IMAGE_CURSOR, SM_CXCURSOR, SM_CYCURSOR, LR_DEFAULTSIZE | LR_SHARED);
	else
		m_Cursore = LoadCursor(m_Istanza, IDC_ARROW);
	if (m_Cursore == nullptr)
		MostraMessaggioDiErrore();
}

/// <summary>
/// https://docs.microsoft.com/it-it/windows/win32/api/winuser/nf-winuser-loadimagea
/// </summary>
/// <param name="idRisorsa">Id dell'icona a risorsa.</param>
/// <todo>Caricamento cursorse personalizzato</todo>
void CWindow::SetIcon(UINT idRisorsa, bool usaCaricamentoAvanzato)
{
	if (usaCaricamentoAvanzato)
		m_IconaFinestra = LoadImage(m_Istanza, MAKEINTRESOURCE(idRisorsa), IMAGE_ICON, SM_CXICON, SM_CYICON, LR_DEFAULTSIZE | LR_SHARED);
	else
		m_IconaFinestra = LoadIcon(m_Istanza, MAKEINTRESOURCE(idRisorsa));
	if (m_IconaFinestra == nullptr)
		MostraMessaggioDiErrore();
}

#pragma endregion

#pragma region Gestione Messaggi

#pragma region Notifiche

void CWindow::OnNotify(UINT idNotificatore, LPNMHDR nmhdr)
{
}

#pragma endregion

#pragma region Scroll Bar

/// <summary>
/// Richiede una implementazione.
/// </summary>
/// <param name="codice"></param>
/// <param name="posizione"></param>
/// <param name="scrollBar">Può essere null.</param>
void CWindow::OnHScroll(UINT codice, int posizione, HANDLE scrollBar)
{
}

/// <summary>
/// Richiede una implementazione.
/// </summary>
/// <param name="codice"></param>
/// <param name="posizione"></param>
/// <param name="scrollBar">Può essere null.</param>
void CWindow::OnVScroll(UINT codice, int posizione, HANDLE scrollBar)
{
}

#pragma endregion 

#pragma region Disegno

/// <summary>
/// La versione base di questa funzione inizia la procedura di disegno.
/// </summary>
void CWindow::OnPaint()
{
	PAINTSTRUCT datiDisegno;
	BeginPaint(m_HandleFinestra, &datiDisegno);
	// Chiama l'implementazione personalizzata.
	OnPaint(&datiDisegno);
	// Questo è da eliminare probabilmente.
	for (auto controllo = m_ControlliFinestra.begin(); controllo != m_ControlliFinestra.end(); controllo++)
		if (controllo->second->m_DisegnoAutonomo)
			controllo->second->OnPaint(&datiDisegno);
	EndPaint(m_HandleFinestra, &datiDisegno);
}

/// <summary>
/// Versione da sovrascrivere.
/// </summary>
/// <param name="datiDisegno"></param>
void CWindow::OnPaint(LPPAINTSTRUCT datiDisegno)
{

}

#pragma endregion

#pragma endregion

#pragma region Operatori

/// <summary>
/// Consente di usare CWindow con le API comuni.
/// </summary>
CWindow::operator HWND()
{
	return m_HandleFinestra;
}

#pragma endregion

/// <summary>
/// Implementazione della procedura.
/// </summary>
/// <param name="hWnd"></param>
/// <param name="messaggio"></param>
/// <param name="wParam"></param>
/// <param name="lParam"></param>
/// <returns></returns>
INT_PTR CWindow::ProceduraFinestra(HWND hWnd, UINT messaggio, WPARAM wParam, LPARAM lParam)
{
	INT_PTR messaggioGestito = FALSE;
	switch (messaggio)
	{
	default:
		messaggioGestito = DefWindowProc(hWnd, messaggio, wParam, lParam);
		break;
	case WM_CLOSE:
	{
		messaggioGestito = TRUE;
		DestroyWindow(m_HandleFinestra);
	}
		break;
	case WM_CREATE:
	{
		CentraFinestra();
		messaggioGestito = TRUE;
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
	case WM_NOTIFY:
	{
		OnNotify(LOWORD(wParam), reinterpret_cast<LPNMHDR>(lParam));
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
	}
	return messaggioGestito;
}

#pragma region Statiche

/// <summary>
/// Procedura come membro di classe, da rimettere in ogni classe derivata probabilmente.
/// https://devblogs.microsoft.com/oldnewthing/20140203-00/?p=1893
/// </summary>
/// <param name="hWnd"></param>
/// <param name="messaggio"></param>
/// <param name="wParam"></param>
/// <param name="lParam"></param>
/// <returns></returns>
INT_PTR CALLBACK CWindow::WndProc(HWND hWnd, UINT messaggio, WPARAM wParam, LPARAM lParam)
{
	CWindow* finestraDiRiferimento = nullptr;
	if (messaggio == WM_NCCREATE)
	{
		LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
		finestraDiRiferimento = static_cast<CWindow *>(lpcs->lpCreateParams);
		// Put the value in a safe place for future use
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(finestraDiRiferimento));
	}
	else
		finestraDiRiferimento = reinterpret_cast<CWindow *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	if (finestraDiRiferimento != nullptr)
		// Now that we have recovered our "this" pointer, let the
		// member function finish the job.
		return finestraDiRiferimento->ProceduraFinestra(hWnd, messaggio, wParam, lParam);
	else
		// We don't know what our "this" pointer is, so just do the default
		// thing. Hopefully, we didn't need to customize the behavior yet.
		return DefWindowProc(hWnd, messaggio, wParam, lParam);
}

#pragma endregion