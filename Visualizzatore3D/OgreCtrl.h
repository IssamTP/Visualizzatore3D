#pragma once

#include "Window.h"

class COgreCtrl : public CWindow
{
protected:
	Ogre::Camera* m_pCamera;
	Ogre::RenderWindow* m_pRenderWindow;
	Ogre::SceneManager* m_pSceneManager;
	Ogre::Viewport* m_pViewport;
public:
	COgreCtrl();
	~COgreCtrl();
	virtual void OnPaint();
	void InizializzaControllo(HWND parentHandle, RECT& dimensioni);
};
