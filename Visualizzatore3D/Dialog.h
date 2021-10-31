#pragma once

#include "Window.h"

class CDialog : public CWindow
{
protected:
	int m_IdRisorsaTemplate;
public:
	CDialog(HINSTANCE istanza, int idRisorsaTemplate);
	~CDialog();
	void CreaDialog(HWND parent);
	void MostraFinestra(int comandoShow);
	inline HWND HandleFinestra()
	{
		return m_HandleFinestra;
	}
protected:
	virtual void CreaControlliDaRisorse() = 0;
	virtual void OnHScroll(WPARAM wParam, LPARAM lParam);
	virtual void OnVScroll(WPARAM wParam, LPARAM lParam);
	friend INT_PTR CALLBACK ProceduraDialog(HWND hWnd, UINT messaggio, WPARAM wParam, LPARAM lParam);
};

