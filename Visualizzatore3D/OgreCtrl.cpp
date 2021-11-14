#include "stdafx.h"
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

Ogre::ManualObject* COgreCtrl::DisegnaCubo(Ogre::String name, Ogre::ResourcePtr risorsa)
{
    Ogre::ManualObject* cube = new Ogre::ManualObject(name);
    cube->begin(Ogre::MaterialManager::getSingleton().getByName("OldMovie"));
    cube->position(0.5f, -0.5f, 1.0f); cube->normal(0.408248f, -0.816497f, 0.408248f); cube->textureCoord(1, 0);
    cube->position(-0.5f, -0.5f, 0.0f); cube->normal(-0.408248f, -0.816497f, -0.408248f); cube->textureCoord(0, 1);
    cube->position(0.5f, -0.5f, 0.0f); cube->normal(0.666667f, -0.333333f, -0.666667f); cube->textureCoord(1, 1);
    cube->position(-0.5f, -0.5f, 1.0f); cube->normal(-0.666667f, -0.333333f, 0.666667f); cube->textureCoord(0, 0);
    cube->position(0.5f, 0.5f, 1.0f); cube->normal(0.666667f, 0.333333f, 0.666667f); cube->textureCoord(1, 0);
    cube->position(-0.5f, -0.5f, 1.0f); cube->normal(-0.666667f, -0.333333f, 0.666667f); cube->textureCoord(0, 1);
    cube->position(0.5f, -0.5f, 1.0f); cube->normal(0.408248f, -0.816497f, 0.408248f); cube->textureCoord(1, 1);
    cube->position(-0.5f, 0.5f, 1.0f); cube->normal(-0.408248f, 0.816497f, 0.408248f); cube->textureCoord(0, 0);
    cube->position(-0.5f, 0.5f, 0.0f); cube->normal(-0.666667f, 0.333333f, -0.666667f); cube->textureCoord(0, 1);
    cube->position(-0.5f, -0.5f, 0.0f); cube->normal(-0.408248f, -0.816497f, -0.408248f); cube->textureCoord(1, 1);
    cube->position(-0.5f, -0.5f, 1.0f); cube->normal(-0.666667f, -0.333333f, 0.666667f); cube->textureCoord(1, 0);
    cube->position(0.5f, -0.5f, 0.0f); cube->normal(0.666667f, -0.333333f, -0.666667f); cube->textureCoord(0, 1);
    cube->position(0.5f, 0.5f, 0.0f); cube->normal(0.408248f, 0.816497f, -0.408248f); cube->textureCoord(1, 1);
    cube->position(0.5f, -0.5f, 1.0f); cube->normal(0.408248f, -0.816497f, 0.408248f); cube->textureCoord(0, 0);
    cube->position(0.5f, -0.5f, 0.0f); cube->normal(0.666667f, -0.333333f, -0.666667f); cube->textureCoord(1, 0);
    cube->position(-0.5f, -0.5f, 0.0f); cube->normal(-0.408248f, -0.816497f, -0.408248f); cube->textureCoord(0, 0);
    cube->position(-0.5f, 0.5f, 1.0f); cube->normal(-0.408248f, 0.816497f, 0.408248f); cube->textureCoord(1, 0);
    cube->position(0.5f, 0.5f, 0.0f); cube->normal(0.408248f, 0.816497f, -0.408248f); cube->textureCoord(0, 1);
    cube->position(-0.5f, 0.5f, 0.0f); cube->normal(-0.666667f, 0.333333f, -0.666667f); cube->textureCoord(1, 1);
    cube->position(0.5f, 0.5f, 1.0f); cube->normal(0.666667f, 0.333333f, 0.666667f); cube->textureCoord(0, 0);
    cube->triangle(0, 1, 2);		cube->triangle(3, 1, 0);
    cube->triangle(4, 5, 6);		cube->triangle(4, 7, 5);
    cube->triangle(8, 9, 10);		cube->triangle(10, 7, 8);
    cube->triangle(4, 11, 12);	cube->triangle(4, 13, 11);
    cube->triangle(14, 8, 12);	cube->triangle(14, 15, 8);
    cube->triangle(16, 17, 18);	cube->triangle(16, 19, 17);
    cube->end();

    return cube;
}

Ogre::ResourcePtr COgreCtrl::CaricaMateriale()
{
    Ogre::MaterialManager* manager = Ogre::MaterialManager::getSingletonPtr();
    return manager->load("OldMovie", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);
}

Ogre::ResourcePtr COgreCtrl::CaricaMesh()
{
    Ogre::ResourceGroupManager& manager = Ogre::ResourceGroupManager::getSingleton();
    Ogre::StringVector gruppi = manager.getResourceGroups();
    for (auto gruppo = gruppi.begin(); gruppo != gruppi.end(); gruppo++)
    {
        if (gruppo->compare("Mesh") == 0)
        {
            auto resLoc = manager.findResourceLocation("Mesh", "*");
            if (resLoc->size() > 0)
            {
                Ogre::String meshLoc = *resLoc->begin();
                Ogre::MeshManager& meshManager = Ogre::MeshManager::getSingleton();
                auto resources = meshManager.getResourceIterator();
                auto resourceIterator = resources.begin();
                while (resourceIterator != resources.end())
                {
                    Ogre::String nomeRisorsa = resourceIterator->second->getName();
                    if (nomeRisorsa.compare("ogrehead") == 0 || nomeRisorsa.compare("Prefab_Cube") == 0)
                        return resourceIterator->second;
                    else
                        resourceIterator++;
                }
            }
        }
    }
    return nullptr;
}

void COgreCtrl::InizializzaControllo(HWND parentHandle, RECT& dimensioni)
{
    unsigned int altezza = static_cast<unsigned int>(dimensioni.bottom - dimensioni.top);
    unsigned int larghezza = static_cast<unsigned int>(dimensioni.right - dimensioni.left);
    Ogre::NameValuePairList miscParams;
    miscParams["parentWindowHandle"] = Ogre::StringConverter::toString((UINT)(parentHandle));
    m_pRenderWindow = OgreApp.m_Root->createRenderWindow("renderctrl", larghezza, altezza, false, &miscParams);
    m_pRenderWindow->setVisible(true);
    m_pSceneManager = OgreApp.CreateSceneManager();
    if (m_pRenderWindow != nullptr && m_pSceneManager != nullptr)
    {
        m_pSceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
        Ogre::Light* light = m_pSceneManager->createLight("IlluminazionePrincipale");
        Ogre::SceneNode* lightNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode();
        lightNode->attachObject(light);
        lightNode->setPosition(20, 80, 50);
        Ogre::SceneNode* camNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode();
        m_pCamera = m_pSceneManager->createCamera("CameraPrincipale");
        m_pCamera->setNearClipDistance(5);
        m_pCamera->setAutoAspectRatio(true);
        camNode->attachObject(m_pCamera);
        camNode->setPosition(0, 0, 10);
        m_pRenderWindow->addViewport(m_pCamera);

        Ogre::SceneNode* ogreNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode();
        Ogre::ResourcePtr resourceMesh = nullptr; // CaricaMesh();
        if (resourceMesh != nullptr)
        {
            //Ogre::MeshPtr mesh = Ogre::MeshPtr(resourceMesh);
            //ogreNode->attachObject(m_pSceneManager->createEntity("Cubo", Ogre::SceneManager::PrefabType::PT_CUBE));
        }
        else
        {
            ogreNode->attachObject(DisegnaCubo("CuboTest", CaricaMateriale()));
        }
        m_pRenderWindow->setActive(true);
    }
}

void COgreCtrl::OnPaint()
{
}