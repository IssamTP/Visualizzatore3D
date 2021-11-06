#pragma once
#include "framework.h"
#include "resource.h"
#include <OGRE\Ogre.h>
#ifdef _DEBUG
	#pragma comment(lib, "E:\\Sviluppo\\Visualizzatore3D\\x64\\Debug\\OgreMain_d.lib")
#else
	#pragma comment(lib,"E:\\Sviluppo\\OGRE\\lib\\OgreMain.lib")
#endif

extern Ogre::Root* g_Root;