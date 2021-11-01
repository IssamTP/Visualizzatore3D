#include "framework.h"
#include "SliderCtrl.h"

CSliderCtrl::CSliderCtrl()
	: CWindow()
{
}

int CSliderCtrl::GetPosizioneCursore()
{
	return static_cast<unsigned int>(SendMessage(m_HandleFinestra, TBM_GETPOS, 0U, 0U));
}

void CSliderCtrl::SetIntervallo(int minimo, int massimo)
{
	if (m_HandleFinestra != nullptr && minimo < massimo)
	{
		SendMessage(m_HandleFinestra, TBM_SETRANGE, TRUE, MAKELONG(minimo, massimo));
		SendMessage(m_HandleFinestra, TBM_SETPOS, TRUE, (massimo - minimo) / 2);
	}
}