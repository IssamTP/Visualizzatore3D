#include "stdafx.h"
#include "OgreApplication.h"

OgreApplication::OgreApplication()
{
    m_Log = m_LogManager.getSingleton().createLog("Ogre.log", true, true, false);
    m_FSLayer = OGRE_NEW Ogre::FileSystemLayer("Visualizzatore3D");
    InizializzaRoot();
    CaricaRisorse();
    InizializzaShader();
    Setup();
}

OgreApplication::~OgreApplication()
{
    OGRE_DELETE m_FSLayer;
    OGRE_DELETE m_Root;
}

void OgreApplication::Log(Ogre::String& messaggio)
{
    m_Log->logMessage(messaggio);
}

SceneManager* OgreApplication::CreateSceneManager()
{
    Ogre::SceneManager* nuovaScena = m_Root->createSceneManager();
    //m_ShaderGenerator->addSceneManager(nuovaScena);
    return nuovaScena;
}

void OgreApplication::CaricaRisorse()
{
    auto& rgm = Ogre::ResourceGroupManager::getSingleton();
    // load resource paths from config file
    Ogre::ConfigFile cf;
    Ogre::String resourcesPath = m_FSLayer->getConfigFilePath("resources.cfg");
    if (Ogre::FileSystemLayer::fileExists(resourcesPath) || OGRE_PLATFORM == OGRE_PLATFORM_EMSCRIPTEN)
    {
        Ogre::LogManager::getSingleton().logMessage("Parsing '" + resourcesPath + "'");
        cf.load(resourcesPath);
    }
    Ogre::String sec, type, arch;
    // go through all specified resource groups
    Ogre::ConfigFile::SettingsBySection_::const_iterator seci;
    for (seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci) {
        sec = seci->first;
        const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
        Ogre::ConfigFile::SettingsMultiMap::const_iterator i;

        // go through all resource paths
        for (i = settings.begin(); i != settings.end(); i++)
        {
            type = i->first;
            arch = i->second;
            Ogre::StringUtil::trim(arch);
            if (arch.empty() || arch[0] == '.')
            {
                // resolve relative path with regards to configfile
                Ogre::String baseDir, filename;
                Ogre::StringUtil::splitFilename(resourcesPath, filename, baseDir);
                arch = baseDir + arch;
            }
            arch = Ogre::FileSystemLayer::resolveBundlePath(arch);
#if OGRE_PLATFORM != OGRE_PLATFORM_EMSCRIPTEN
            if ((type == "Zip" || type == "FileSystem") && !Ogre::FileSystemLayer::fileExists(arch))
            {
                Ogre::LogManager::getSingleton().logWarning("resource location '" + arch + "' does not exist - skipping");
                continue;
            }
#endif
            rgm.addResourceLocation(arch, type, sec);
        }
    }

    //        if (rgm.getResourceLocationList(Ogre::RGN_INTERNAL).empty())
    //        {
    //            const auto& mediaDir = getDefaultMediaDir();
    //            // add default locations
    //            rgm.addResourceLocation(mediaDir + "/Main", "FileSystem", Ogre::RGN_INTERNAL);
    //#ifdef OGRE_BUILD_COMPONENT_TERRAIN
    //            rgm.addResourceLocation(mediaDir + "/Terrain", "FileSystem", Ogre::RGN_INTERNAL);
    //#endif
    //#ifdef OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
    //            rgm.addResourceLocation(mediaDir + "/RTShaderLib/GLSL", "FileSystem", Ogre::RGN_INTERNAL);
    //            rgm.addResourceLocation(mediaDir + "/RTShaderLib/HLSL_Cg", "FileSystem", Ogre::RGN_INTERNAL);
    //#endif
    //        }
}

void OgreApplication::InizializzaRoot()
{
    m_Root = OGRE_NEW Ogre::Root(m_FSLayer->getConfigFilePath("plugins.cfg"), m_FSLayer->getWritablePath("ogre.cfg"), m_FSLayer->getWritablePath("ogre.log"));
}

void OgreApplication::InizializzaShader()
{
    //if (Ogre::RTShader::ShaderGenerator::initialize() && false)
    //{
    //    m_ShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    //    m_ShaderGenerator->setShaderCachePath("");
    //    // Create and register the material manager listener if it doesn't exist yet.
    //    if (m_MaterialMgrListener == nullptr)
    //    {
    //        m_MaterialMgrListener = new OgreBites::SGTechniqueResolverListener(m_ShaderGenerator);
    //        Ogre::MaterialManager::getSingleton().addListener(m_MaterialMgrListener);
    //    }
    //}
}

void OgreApplication::Setup()
{

    Ogre::RenderSystemList renderers = m_Root->getAvailableRenderers();
    Ogre::RenderSystemList::iterator it = renderers.begin();
    Ogre::RenderSystem* renderer = nullptr;
    while (it != renderers.end())
    {
        renderer = *it;
        Ogre::String nome = renderer->getName();
        if (renderer->getName().compare(C_DIRECT_3D9_RENDERER) == 0)
        {
            m_Root->setRenderSystem(renderer);
            break;
        }
        ++it;
    }
    renderer = m_Root->getRenderSystem();
    if (renderer != nullptr)
    {
        renderer->setConfigOption("Full Screen", "No");
        renderer->setConfigOption("VSync", "Yes");
    }

    if (!m_Root->restoreConfig())
        m_Root->showConfigDialog(nullptr);
    m_Root->initialise(false);
}

OgreApplication OgreApp;