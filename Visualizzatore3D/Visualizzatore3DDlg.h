#pragma once

#include "Dialog.h"
#include "ListCtrl.h"
#include "OgreCtrl.h"
#include "SliderCtrl.h"

class CVisualizzatore3DDlg : public CDialog
{
protected:
	CSliderCtrl* m_HSlider;
	CSliderCtrl* m_VSlider;
	CListCtrl* m_Texture;
	CWindow* m_Segnaposto;
	COgreCtrl* m_pOgre;
public:
	CVisualizzatore3DDlg(HINSTANCE istanza, int idRisorsa);
	~CVisualizzatore3DDlg();
	virtual void CreaDialog(HWND parent);
protected:
	virtual void CreaControlliDaRisorse();
	virtual void OnHScroll(WPARAM wParam, LPARAM lParam);
	virtual void OnNotify(HWND hWnd, UINT messaggio, WPARAM wParam, LPARAM lParam);
	virtual void OnVScroll(WPARAM wParam, LPARAM lParam);
	virtual void CreaControlloOgre();
};

