#include "Visualizzatore3D.h"
#include "OgreCtrl.h"

COgreCtrl::COgreCtrl()
	: CWindow()
{
    m_DisegnoAutonomo = true;
    m_pOgreRoot = new Ogre::Root(Ogre::String(), Ogre::String(), "Ogre.log");
}

COgreCtrl::~COgreCtrl()
{
    delete m_pOgreRoot;
}

void COgreCtrl::InizializzaControllo()
{
    Ogre::RenderSystemList renderers = m_pOgreRoot->getAvailableRenderers();
    Ogre::RenderSystem* pRenderSystem = nullptr;
    for (Ogre::RenderSystemList::iterator it = renderers.begin(); it != renderers.end(); ++it)
    {
        Ogre::RenderSystem* pSystem = *it;
        if (pSystem != nullptr)
        {
            if (pSystem->getName() == "Direct3D9 Rendering SubSystem")
            {
                // favorize D3D9
                pRenderSystem = pSystem;
                break;
            }
            else if (pSystem->getName() == "OpenGL Rendering SubSystem"
                && pRenderSystem->getName() != "Direct3D9 Rendering SubSystem")
            {
                // if no D3D9 avail, then take OpenGL
                pRenderSystem = pSystem;
                break;
            }
            else if (pSystem->getName() == "Direct3D7 Rendering SubSystem"
                && pRenderSystem->getName() != "Direct3D9 Rendering SubSystem"
                && pRenderSystem->getName() != "OpenGL Rendering SubSystem")
            {
                // well if this system sucks so hard, then take D3D7
                pRenderSystem = pSystem;
                break;
            }
        }
        pRenderSystem->setConfigOption("Full Screen", "No");
        pRenderSystem->setConfigOption("VSync", "Yes");
        pRenderSystem->setConfigOption("Anti aliasing", "No");
        pRenderSystem->setConfigOption("Video Mode", "640 x 480 @ 32-bit colour");

        // tell Ogre about the render system
        m_pOgreRoot->setRenderSystem(pRenderSystem);
        m_pOgreRoot->initialise(false);

        // Compose RT properties
        Ogre::NameValuePairList Properties;
        Properties.insert(
            Ogre::NameValuePairList::value_type("externalWindowHandle", Ogre::StringConverter::toString((long)m_HandleFinestra)));

        // get client rect
        RECT rectClient;
        GetClientRect(m_HandleFinestra, &rectClient);

        // create render window
        m_pRenderWindow = m_pOgreRoot->createRenderWindow("renderwin", rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, false, &Properties);
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
}

void COgreCtrl::OnPaint()
{
    Ogre::Root::getSingleton().renderOneFrame();
}