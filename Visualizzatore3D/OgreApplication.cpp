#include "stdafx.h"
#include "OgreApplication.h"

OgreApplication::OgreApplication()
{
    m_Log = m_LogManager.getSingleton().createLog("Ogre.log", true, true, false);
    InizializzaConfigurazioni();
    InizializzaRoot();
    CaricaRisorse();
    Setup();
}

OgreApplication::~OgreApplication()
{
    auto& rgm = ResourceGroupManager::getSingleton();
    /*rgm.unloadResourceGroup("General");
    rgm.clearResourceGroup("General");*/
    Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);
    if (m_MaterialMgrListener != nullptr)
    {
        Ogre::MaterialManager::getSingleton().removeListener(m_MaterialMgrListener);
        delete m_MaterialMgrListener;
        m_MaterialMgrListener = nullptr;
    }
    if (m_ShaderGenerator != nullptr)
    {
        Ogre::RTShader::ShaderGenerator::destroy();
        m_ShaderGenerator = nullptr;
    }
    m_Root->saveConfig();
    m_Root->shutdown();
    OGRE_DELETE m_Root;
    delete m_FSLayer;
}

void OgreApplication::Log(Ogre::String& messaggio)
{
    m_Log->logMessage(messaggio);
}

SceneManager* OgreApplication::CreateSceneManager()
{
    Ogre::SceneManager* nuovaScena = m_Root->createSceneManager();
    m_SceneManager = nuovaScena;
    if (m_ShaderGenerator == nullptr)
        InizializzaShader();
    m_ShaderGenerator->addSceneManager(nuovaScena);
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
    if (rgm.getResourceLocationList(Ogre::RGN_INTERNAL).empty())
    {
        const Ogre::String& mediaDir = "E:/Sviluppo/Visualizzatore3D/x64/Debug/Media";
        // add default locations
        rgm.addResourceLocation(mediaDir + "/Main", "FileSystem", Ogre::RGN_INTERNAL);
        rgm.addResourceLocation(mediaDir + "/Terrain", "FileSystem", Ogre::RGN_INTERNAL);
        rgm.addResourceLocation(mediaDir + "/RTShaderLib/GLSL", "FileSystem", Ogre::RGN_INTERNAL);
        rgm.addResourceLocation(mediaDir + "/RTShaderLib/HLSL_Cg", "FileSystem", Ogre::RGN_INTERNAL);
    }
}

void OgreApplication::InizializzaConfigurazioni()
{
    TCHAR percorsoProgramma[_MAX_PATH];
    m_FSLayer = new Ogre::FileSystemLayer("Visualizzatore3D");
    GetModuleFileName(nullptr, percorsoProgramma, _MAX_PATH);
    std::wstring conversione(percorsoProgramma);
    conversione = conversione.substr(0, conversione.find_last_of(_T('\\')));
    Ogre::String configDir = Ogre::StringUtil::standardisePath(std::string(conversione.begin(), conversione.end()).c_str());
    m_FSLayer->setConfigPaths({ configDir });
}

void OgreApplication::InizializzaRoot()
{
    m_Root = OGRE_NEW Ogre::Root(m_FSLayer->getConfigFilePath("plugins.cfg"), m_FSLayer->getWritablePath("ogre.cfg"), m_FSLayer->getWritablePath("ogre.log"));
    if (m_Root->getInstalledPlugins().size() == 0)
        m_CaricatorePlugin.load();
    if (m_Root->getAvailableRenderers().empty())
    {
        Ogre::LogManager::getSingleton().logError("No RenderSystems available");
        throw std::exception();
    }
    if (!m_Root->restoreConfig())
        m_Root->showConfigDialog(OgreBites::getNativeConfigDialog());
    m_Root->initialise(false);
}

void OgreApplication::InizializzaShader()
{
#define RTSHADER_SYSTEM_BUILD_CORE_SHADERS
    if (ShaderGenerator::initialize())
    {
        m_ShaderGenerator = ShaderGenerator::getSingletonPtr();
        m_ShaderGenerator->setShaderCachePath("");
        // Create and register the material manager listener if it doesn't exist yet.
        if (m_MaterialMgrListener == nullptr)
        {
            m_MaterialMgrListener = new OgreBites::SGTechniqueResolverListener(m_ShaderGenerator);
            Ogre::MaterialManager::getSingleton().addListener(m_MaterialMgrListener);
        }
    }
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
        if (renderer->getName().compare(C_DIRECT_3D11_RENDERER) == 0)
        {
            m_Root->setRenderSystem(renderer);
            break;
        }
        ++it;
    }
}

OgreApplication OgreApp;