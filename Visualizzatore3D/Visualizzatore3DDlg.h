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
	virtual void CreaFinestra(HWND parent) override;
protected:
	virtual void CreaControlliDaRisorse();
	virtual void OnClose() override;
	virtual void OnHScroll(UINT operazione, int posizione, HANDLE scrollBar) override;
	virtual void OnNotify(UINT idNotificatore, LPNMHDR nmhdr) override;
	virtual void OnVScroll(UINT operazione, int posizione, HANDLE scrollBar) override;
	void CreaControlloOgre();
	HIMAGELIST CreaImageList();
};

