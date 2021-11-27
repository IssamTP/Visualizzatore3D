#pragma once

#include "Window.h"

/// <summary>
/// TODO:
/// 1) Inserire gli assi nel controllo per avere riscontro della rotazione.
/// 2) Migliorare la rotazione.
/// </summary>
class COgreCtrl : public CWindow
{
protected:
	Ogre::Camera* m_pCamera;
	Ogre::ManualObject* m_Cubo;
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
	void LiberaRisorseOgre();
protected:
	void CaricaNomiMateriali();
	Ogre::ManualObject* CreaCubo(Ogre::String name, Ogre::MaterialPtr materialeDaUsare);
};
