#pragma once

// ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#define WIN32_LEAN_AND_MEAN           

// ����� ���� ����� ���
#define DEBUG_MODE

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#include <Ogre.h>
#include <OIS/OIS.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <map>

using namespace Ogre;
using namespace std;

// ����� ���� Ŭ���� 
// << ��ü ���� >>
#include "cSingleton.h"
#include "CoreStorage.h"

// << ����ü >>
#include "StructData.h"

//// << �Ϲ� Ŭ���� >>
//#include "cCam.h"
//#include "cLightManager.h"
//#include "cModelManager.h"
//#include "cShaderManager.h"
//#include "cMaterialManager.h"
//#include "cdrawManager.h"

