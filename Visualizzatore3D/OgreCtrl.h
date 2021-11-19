#pragma once

#include "Window.h"

class COgreCtrl : public CWindow
{
protected:
	Ogre::Camera* m_pCamera;
	Ogre::Radian m_Rotazione;
	Ogre::RenderWindow* m_pRenderWindow;
	std::vector<Ogre::ResourcePtr> m_MaterialiCaricati;
	Ogre::SceneManager* m_pSceneManager;
	Ogre::Viewport* m_pViewport;
public:
	COgreCtrl();
	~COgreCtrl();
	void CaricaMateriali();
	void ImpostaMateriale(Ogre::String nomeMateriale);
	void ImpostaRotazione(int angoloSessagesimale, unsigned short asse);
	void InizializzaControllo(HWND parentHandle, RECT& dimensioni);
	Ogre::ResourcePtr CaricaMesh();
protected:
	Ogre::ManualObject* DisegnaCubo(Ogre::String name, Ogre::ResourcePtr matName);
};
