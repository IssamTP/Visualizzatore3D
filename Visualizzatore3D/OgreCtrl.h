#pragma once

#include "Window.h"

class COgreCtrl : public CWindow, public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
	COgreCtrl();
	void InizializzaControllo();
};
