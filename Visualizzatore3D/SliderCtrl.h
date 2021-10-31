#pragma once

#include "Window.h"



class CSliderCtrl : public CWindow
{
public:
	enum E_TIPI_SLIDER
	{
		CTL = SB_CTL,
		STD_HORZ = SB_HORZ,
		STD_VERT = SB_VERT,
	};
protected:
	int m_Massimo;
	int m_Minimo;
	E_TIPI_SLIDER m_TipoSlider;
public:
	CSliderCtrl();
	void SetIntervallo(unsigned int minimo, unsigned int massimo);
};

