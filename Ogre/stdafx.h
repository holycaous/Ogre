#pragma once

// 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#define WIN32_LEAN_AND_MEAN           

// 사용자 임의 디버그 모드
#define DEBUG_MODE

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#include <Ogre.h>
#include <OIS/OIS.h>
#include <Overlay/OgreOverlay.h>
#include <Overlay/OgreOverlaySystem.h>
#include <Overlay/OgreOverlayManager.h>
#include <Overlay/OgreOverlayElement.h>
#include <Overlay/OgreTextAreaOverlayElement.h>
#include <Overlay/OgreFontManager.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <list>
#include <map>

using namespace Ogre;
using namespace std;

// 사용자 정의 클래스 
// << 전체 공통 >>
#include "cSingleton.h"
#include "CoreStorage.h"

// << 구조체 >>
#include "StructData.h"

//// << 일반 클래스 >>
#include "Cam.h"
#include "LightManager.h"
#include "ModelManager.h"
#include "ListenerManager.h"
//#include "cShaderManager.h"
//#include "cMaterialManager.h"
//#include "cdrawManager.h"

