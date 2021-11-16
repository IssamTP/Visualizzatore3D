#pragma once

#include "Window.h"

class COgreCtrl : public CWindow
{
protected:
	Ogre::Camera* m_pCamera;
	Ogre::Radian m_Rotazione;
	Ogre::RenderWindow* m_pRenderWindow;
	Ogre::SceneManager* m_pSceneManager;
	Ogre::Viewport* m_pViewport;
public:
	COgreCtrl();
	~COgreCtrl();
	virtual void OnPaint();
	Ogre::ResourcePtr CaricaMateriale();
	Ogre::ResourcePtr CaricaMesh();
	void ImpostaRotazione(int angoloSessagesimale, unsigned short asse);
	void InizializzaControllo(HWND parentHandle, RECT& dimensioni);
protected:
	Ogre::ManualObject* DisegnaCubo(Ogre::String name, Ogre::ResourcePtr matName);
};
