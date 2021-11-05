#pragma once

#include "Window.h"

class CDialog : public CWindow
{
protected:
	int m_IdRisorsaTemplate;
public:
	CDialog(HINSTANCE istanza, int idRisorsaTemplate);
	~CDialog();
	virtual void CreaDialog(HWND parent);
	void MostraFinestra(int comandoShow);
	inline HWND HandleFinestra()
	{
		return m_HandleFinestra;
	}
protected:
	virtual void CreaControlliDaRisorse() = 0;
	friend INT_PTR CALLBACK ProceduraDialog(HWND hWnd, UINT messaggio, WPARAM wParam, LPARAM lParam);
};

