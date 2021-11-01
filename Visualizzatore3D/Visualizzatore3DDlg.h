#pragma once

#include "Dialog.h"
#include "SliderCtrl.h"

class CVisualizzatore3DDlg : public CDialog
{
protected:
	CSliderCtrl* m_HSlider;
	CSliderCtrl* m_VSlider;
public:
	CVisualizzatore3DDlg(HINSTANCE istanza, int idRisorsa);
protected:
	virtual void CreaControlliDaRisorse();
	virtual void OnHScroll(WPARAM wParam, LPARAM lParam);
	virtual void OnVScroll(WPARAM wParam, LPARAM lParam);
};

