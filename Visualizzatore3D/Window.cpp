#include "Visualizzatore3D.h"
#include "Window.h"

CWindow::CWindow()
{
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