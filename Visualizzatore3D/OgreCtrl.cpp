#include "Visualizzatore3D.h"
#include "OgreCtrl.h"

COgreCtrl::COgreCtrl()
	: CWindow()
{
    m_DisegnoAutonomo = true;
    m_pCamera = nullptr;
    m_pRenderWindow = nullptr;
    m_pSceneManager = nullptr;
    m_pViewport = nullptr;
}

COgreCtrl::~COgreCtrl()
{
}

void COgreCtrl::InizializzaControllo(HWND parentHandle, RECT& dimensioni)
{
    unsigned int altezza = static_cast<unsigned int>(dimensioni.bottom - dimensioni.top);
    unsigned int larghezza = static_cast<unsigned int>(dimensioni.right - dimensioni.left);
    Ogre::NameValuePairList miscParams;
    miscParams["parentWindowHandle"] = Ogre::StringConverter::toString((UINT)(parentHandle));
    m_pRenderWindow = g_Root->createRenderWindow("renderctrl", larghezza, altezza, false, &miscParams);
    m_pRenderWindow->setVisible(true);
    if (m_pRenderWindow != nullptr)
    {
        // Create a generic scene manager as we won't do anything too fancy
        if (m_pSceneManager!= nullptr)
        {
            // Create camera
            m_pCamera = m_pSceneManager->createCamera("PhyCoCam");
            if (m_pCamera != nullptr)
            {
                m_pCamera->setNearClipDistance(1.0);
                m_pCamera->setFarClipDistance(500000.0);

                // Create viewport
                m_pViewport = m_pRenderWindow->addViewport(m_pCamera);
                if (NULL != m_pViewport)
                {
                    m_pViewport->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0));
                    m_pViewport->setClearEveryFrame(true);

                    // Create light source
                    Ogre::Light* pLight = m_pSceneManager->createLight("PhyCoLight");
                    if (pLight != nullptr)
                    {
                        pLight->setDiffuseColour(1.0, 1.0, 1.0);
                        pLight->setType(Ogre::Light::LT_POINT);
                        Ogre::SceneNode* pLightNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode("PhyCoLightNode");
                        pLightNode->attachObject(pLight);
                        pLightNode->setVisible(true);
                        pLight->setVisible(true);
                    }
                }
            }
        }

        // activate render window and post a single update
        m_pRenderWindow->setActive(true);
        m_pRenderWindow->update();
    }
}

void COgreCtrl::OnPaint()
{
    Ogre::Root::getSingleton().renderOneFrame();
}