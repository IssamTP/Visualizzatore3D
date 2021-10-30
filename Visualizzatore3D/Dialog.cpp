#include "framework.h"
#include "Dialog.h"

CDialog::CDialog(HINSTANCE istanza, int idRisorsaTemplate)
{
	m_IdRisorsaTemplate = idRisorsaTemplate;
	m_Istanza = istanza;
}

void CDialog::CreaDialog(HWND parent)
{
	CreateDialog(m_Istanza, MAKEINTRESOURCE(m_IdRisorsaTemplate), parent, &ProceduraDialog);
}

INT_PTR CDialog::ProceduraDialog(UINT messaggio, WPARAM wParam, LPARAM lParam)
{
	INT_PTR messaggioGestito = FALSE;
	switch (messaggio)
	{
	case WM_CLOSE:
		messaggioGestito = TRUE;
		DestroyWindow()
		break;
	case WM_DESTROY:
		messaggioGestito = TRUE;
		break;
	}
	return messaggioGestito;
}