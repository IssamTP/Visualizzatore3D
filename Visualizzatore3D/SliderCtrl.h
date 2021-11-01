#pragma once

#include "Window.h"



class CSliderCtrl : public CWindow
{
public:
	CSliderCtrl();
	int GetPosizioneCursore();
	void SetIntervallo(int minimo, int massimo);
};

