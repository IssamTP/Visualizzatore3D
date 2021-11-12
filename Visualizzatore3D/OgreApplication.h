#pragma once

using namespace Ogre;

class OgreApplication
{
    const String C_DIRECT_3D9_RENDERER = "Direct3D9 Rendering Subsystem";
    const String C_DIRECT_3D11_RENDERER = "Direct3D11 Rendering Subsystem";
    const String C_OPEN_GL_RENDERER = "OpenGL Rendering Subsystem";
protected:
    FileSystemLayer* m_FSLayer;
    Log* m_Log;
    LogManager* m_LogManager;
    //Ogre::RTShader::ShaderGenerator* m_ShaderGenerator;
    //OgreBites::SGTechniqueResolverListener* m_MaterialMgrListener;
public:
    Root* m_Root;
public:
    OgreApplication();
    ~OgreApplication();
    void Log(Ogre::String& messaggio);
    SceneManager* CreateSceneManager();
protected:
    void CaricaRisorse();
    void InizializzaRoot();
    void InizializzaShader();
    void Setup();
};

extern OgreApplication OgreApp;