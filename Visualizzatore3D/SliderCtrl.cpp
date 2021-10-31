#include "framework.h"
#include "SliderCtrl.h"

CSliderCtrl::CSliderCtrl()
	: CWindow()
{
	m_Minimo = 0U;
	m_Massimo = 0U;
	m_TipoSlider = CTL;
}

void CSliderCtrl::SetIntervallo(unsigned int minimo, unsigned int massimo)
{
	if (m_HandleFinestra != nullptr && minimo < massimo)
	{
		m_Minimo = minimo;
		m_Massimo = massimo;
		SetScrollRange(m_HandleFinestra, static_cast<int>(m_TipoSlider), m_Minimo, m_Massimo, TRUE);
	}
}