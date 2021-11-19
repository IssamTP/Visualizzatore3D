#include "stdafx.h"
#include "Visualizzatore3D.h"
#include "OgreCtrl.h"

COgreCtrl::COgreCtrl()
	: CWindow()
{
    m_DisegnoAutonomo = false;
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
    cube->begin(Ogre::MaterialManager::getSingleton().getByName(risorsa->getName()));
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
    cube->setDynamic(true);

    return cube;
}

void COgreCtrl::CaricaMateriali()
{
    Ogre::MaterialManager* manager = Ogre::MaterialManager::getSingletonPtr();
    m_MaterialiCaricati.push_back(manager->load("OldMovie", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true));
    m_MaterialiCaricati.push_back(manager->load("Ogre", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true));
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
                    if (nomeRisorsa.compare("ogrehead") == 0/* || nomeRisorsa.compare("Prefab_Cube") == 0*/)
                        return resourceIterator->second;
                    else
                        resourceIterator++;
                }
            }
        }
    }
    return nullptr;
}

void COgreCtrl::ImpostaMateriale(Ogre::String nomeMateriale)
{
    Ogre::SceneNode* nodoOgre = dynamic_cast<SceneNode*>(m_pSceneManager->getRootSceneNode()->getChild("NodoCubo"));
    auto oggetti = nodoOgre->getAttachedObjects();
    MaterialPtr materiale = Ogre::MaterialManager::getSingleton().getByName(nomeMateriale);
    for (auto oggetto : oggetti)
    {
        reinterpret_cast<Entity*>(oggetto)->setMaterial(materiale);
    }
    /*Ogre::MovableObject* pMovableCube = nodoOgre->getAttachedObject("CuboTest");
    /*Ogre::ManualObject* pCubo = dynamic_cast<ManualObject*>(pMovableCube);
    /*
    /*auto sezioni = pCubo->getSections();
    for (auto sezione = sezioni.begin(); sezione != sezioni.end(); sezione++)
        (*sezione)->setMaterial(materiale);*/
    m_pRenderWindow->update();
}

void COgreCtrl::ImpostaRotazione(int angoloSessagesimale, unsigned short asse)
{
    constexpr Real degARad = M_PI / 180.0F;
    m_Rotazione = angoloSessagesimale * degARad;
    if (m_pSceneManager != nullptr)
    {
        Ogre::SceneNode* nodoOgre = dynamic_cast<SceneNode*>(m_pSceneManager->getRootSceneNode()->getChild("NodoCubo"));
        switch (asse)
        {
        case 0:
            nodoOgre->rotate(Vector3::UNIT_Z, m_Rotazione);
            break;
        case 1:
            nodoOgre->rotate(Vector3::UNIT_X, m_Rotazione);
            break;
        }
        m_pRenderWindow->update();
    }
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
        camNode->setPosition(0, 0, 50);
        m_pRenderWindow->addViewport(m_pCamera);

        Ogre::SceneNode* ogreNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode("NodoCubo");
        Ogre::ResourcePtr resourceMesh = CaricaMesh();
        CaricaMateriali();
        if (resourceMesh != nullptr || true)
        {
            Ogre::MeshPtr mesh = Ogre::MeshPtr(MeshManager::getSingleton().load("ogrehead.mesh", "Mesh"));
            
            ogreNode->attachObject(m_pSceneManager->createEntity(mesh/*"Cubo", Ogre::SceneManager::PrefabType::PT_CUBE*/));
        }
        else
        {
            ogreNode->attachObject(DisegnaCubo("CuboTest", m_MaterialiCaricati[0]));
            ManualObject* cubo = reinterpret_cast<ManualObject *>(ogreNode->getAttachedObject("CuboTest"));
            ogreNode->rotate(Vector3::UNIT_Z, Radian(0.0));
        }
        m_pRenderWindow->setActive(true);
        m_pRenderWindow->update();
    }
}