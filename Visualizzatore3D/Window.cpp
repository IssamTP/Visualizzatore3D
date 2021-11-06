#include "Visualizzatore3D.h"
#include "Window.h"

CWindow::CWindow()
{
	m_DisegnoAutonomo = false;
	m_Istanza = nullptr;
	m_HandleFinestra = nullptr;
}

void CWindow::MostraMessaggioDiErrore()
{
	DWORD ultimoErrore = GetLastError();
	DWORD specifiche = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
	LPTSTR messaggio = nullptr;
	FormatMessage(specifiche, nullptr, ultimoErrore, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), messaggio, 1024, nullptr);
	MessageBox(m_HandleFinestra, messaggio, L"Messaggio di Sistema", MB_OK | MB_ICONERROR);
	LocalFree(messaggio);
}

void CWindow::OnNotify(LPNMHDR pNMHDR)
{

}

void CWindow::OnHScroll(WPARAM wParam, LPARAM lParam)
{

}

void CWindow::OnPaint()
{
	for (auto controllo = m_ControlliFinestra.begin(); controllo != m_ControlliFinestra.end(); controllo++)
	{
		if (controllo->second->m_DisegnoAutonomo)
		{
			controllo->second->OnPaint();
		}
	}
}

void CWindow::OnVScroll(WPARAM wParam, LPARAM lParam)
{

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