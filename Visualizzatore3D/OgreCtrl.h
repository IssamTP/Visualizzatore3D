#pragma once

#include "Window.h"

class COgreCtrl : public CWindow
{
protected:
	Ogre::Camera* m_pCamera;
	Ogre::Root* m_pOgreRoot;
	Ogre::RenderWindow* m_pRenderWindow;
	Ogre::SceneManager* m_pSceneManager;
	Ogre::Viewport* m_pViewport;
public:
	COgreCtrl();
	~COgreCtrl();
	virtual void OnPaint();
	void InizializzaControllo();
	inline Ogre::Root* POgreRoot()
	{
		return m_pOgreRoot;
	}
};
