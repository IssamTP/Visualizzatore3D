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
	COgreCtrl* m_pOgre;
public:
	CVisualizzatore3DDlg(HINSTANCE istanza, int idRisorsa);
	virtual void CreaDialog(HWND parent);
protected:
	virtual void CreaControlliDaRisorse();
	virtual void OnHScroll(WPARAM wParam, LPARAM lParam);
	virtual void OnNotify(LPNMHDR pNMHDR);
	virtual void OnVScroll(WPARAM wParam, LPARAM lParam);
	virtual void CreaControlloOgre();
};

