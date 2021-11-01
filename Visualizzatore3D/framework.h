// header.h: file di inclusione per file di inclusione di sistema standard
// o file di inclusione specifici del progetto
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Escludere gli elementi usati raramente dalle intestazioni di Windows
// File di intestazione di Windows
#include <windows.h>
#include <CommCtrl.h>
#pragma comment(lib, "ComCtl32.lib")
#pragma comment(linker, \
  "\"/manifestdependency:type='Win32' "\
  "name='Microsoft.Windows.Common-Controls' "\
  "version='6.0.0.0' "\
  "processorArchitecture='*' "\
  "publicKeyToken='6595b64144ccf1df' "\
  "language='*'\"")
// File di intestazione Runtime C
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <map>
#include <vector>
#include <string>
