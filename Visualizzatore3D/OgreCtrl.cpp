#include "stdafx.h"
#include "Visualizzatore3D.h"
#include "OgreCtrl.h"

using namespace Ogre;

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

void COgreCtrl::CaricaNomiMateriali()
{
    auto& rgm = ResourceGroupManager::getSingleton();
    rgm.initialiseResourceGroup("General");
    ResourceManager::ResourceMapIterator materiali = MaterialManager::getSingletonPtr()->getResourceIterator();
    for (auto materiale = materiali.begin(); materiale != materiali.end(); materiale++)
        m_ListaNomiMateriali.insert(m_ListaNomiMateriali.end(), materiale->second.get()->getName());
    std::sort(m_ListaNomiMateriali.begin(), m_ListaNomiMateriali.end());
}

void COgreCtrl::GetNomiMateriali(std::vector<std::wstring>& nomiMateriali)
{
    nomiMateriali.resize(m_ListaNomiMateriali.size());
    for (UINT materiale = 0u; materiale < m_ListaNomiMateriali.size(); materiale++)
        nomiMateriali[materiale] = std::wstring(m_ListaNomiMateriali[materiale].begin(), m_ListaNomiMateriali[materiale].end());
}

void COgreCtrl::ImpostaMateriale(String nomeMateriale)
{
    try
    {
        auto* nodo = m_pSceneManager->getSceneNode("NodoCubo");
        auto* cubo = reinterpret_cast<ManualObject *>(nodo->getAttachedObject("CuboTest"));
        MaterialPtr materialeDaUsare = MaterialManager::getSingletonPtr()->getByName(nomeMateriale);
        if (materialeDaUsare != nullptr)
            cubo->setMaterial(0u, materialeDaUsare);
    }
    catch (std::exception eccezione)
    {
        std::cout << eccezione.what();
    }
    m_pRenderWindow->update();
}

void COgreCtrl::ImpostaRotazione(int angoloSessagesimale, unsigned short asse)
{
    constexpr Real degARad = static_cast<Real>(M_PI) / 180.0F;
    m_Rotazione = angoloSessagesimale * degARad;
    if (m_pSceneManager != nullptr)
    {
        SceneNode* nodoOgre = dynamic_cast<SceneNode*>(m_pSceneManager->getRootSceneNode()->getChild("NodoCubo"));
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
        Light* light = m_pSceneManager->createLight("IlluminazionePrincipale");
        SceneNode* lightNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode();
        lightNode->attachObject(light);
        lightNode->setPosition(20, 80, 50);
        SceneNode* camNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode();
        m_pCamera = m_pSceneManager->createCamera("CameraPrincipale");
        m_pCamera->setNearClipDistance(5);
        m_pCamera->setAutoAspectRatio(true);
        camNode->attachObject(m_pCamera);
        camNode->setPosition(0, 0, 10);
        m_pRenderWindow->addViewport(m_pCamera);
        CaricaNomiMateriali();
        SceneNode* ogreNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode("NodoCubo");
        ogreNode->attachObject(CreaCubo("CuboTest", MaterialManager::getSingletonPtr()->getByName("OldMovie")));
        ManualObject* cubo = reinterpret_cast<ManualObject *>(ogreNode->getAttachedObject("CuboTest"));
        ogreNode->rotate(Vector3::UNIT_Z, Radian(0.0));
        m_pRenderWindow->setActive(true);
        m_pRenderWindow->update();
    }
}

ManualObject* COgreCtrl::CreaCubo(String name, MaterialPtr materialeDaUsare)
{
    Ogre::ManualObject* cube = new Ogre::ManualObject(name);
    cube->begin(materialeDaUsare);
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
