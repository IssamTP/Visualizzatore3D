#pragma once

#include "Window.h"

class CDialog : public CWindow
{
protected:
	int m_IdRisorsaTemplate;
public:
	CDialog(HINSTANCE istanza, UINT idNomeFinestra, int idRisorsaTemplate);
	~CDialog();
	virtual void CreaFinestra(HWND parent) override;
protected:
	virtual void CreaControlliDaRisorse() = 0;
	INT_PTR ProceduraDialog(HWND hWnd, UINT messaggio, WPARAM wParam, LPARAM lParam);
private:
	static INT_PTR CALLBACK DlgProc(HWND hWnd, UINT messaggio, WPARAM wParam, LPARAM lParam);
};

