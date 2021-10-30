#pragma once

class CDialog
{
protected:
	int m_IdRisorsaTemplate;
	HINSTANCE m_Istanza;
public:
	CDialog(HINSTANCE istanza, int idRisorsaTemplate);
	void CreaDialog(HWND parent);
protected:
	INT_PTR ProceduraDialog(UINT messaggio, WPARAM wParam, LPARAM lParam);
};

