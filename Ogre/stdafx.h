#pragma once

// 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#define WIN32_LEAN_AND_MEAN           

// 사용자 임의 디버그 모드
//#define DEBUG_MODE

// 맵 사이즈
#define MAP_SIZE 7500

// 몬스터 기본 갯수
#define MOB_MIN_AMOUNT 30

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
#include <conio.h>
#include <string>
#include <algorithm>
#include <vector>
#include <list>
#include <map>
#include <mmsystem.h>

// 10 진수 itoa
void itoa10(int n, char *buf);

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
#include "SoundManager.h"
#include "LightManager.h"
#include "ModelManager.h"
#include "PostEffect.h"
#include "ListenerManager.h"
//#include "cShaderManager.h"
//#include "cMaterialManager.h"
//#include "cdrawManager.h"

