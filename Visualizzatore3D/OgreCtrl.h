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
	std::vector<std::string> m_ListaNomiMateriali;
public:
	COgreCtrl();
	~COgreCtrl();
	void GetNomiMateriali(std::vector<std::wstring>& nomiMateriali);
	void ImpostaMateriale(Ogre::String nomeMateriale);
	void ImpostaRotazione(int angoloSessagesimale, unsigned short asse);
	void InizializzaControllo(HWND parentHandle, RECT& dimensioni);
	Ogre::ResourcePtr CaricaMesh();
protected:
	void CaricaNomiMateriali();
	Ogre::ManualObject* CreaCubo(Ogre::String name, Ogre::MaterialPtr materialeDaUsare);
};
