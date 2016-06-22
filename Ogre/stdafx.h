#pragma once

// ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#define WIN32_LEAN_AND_MEAN           

// ����� ���� ����� ���
//#define DEBUG_MODE

// �� ������
#define MAP_SIZE 7500

// ���� �⺻ ����
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

// 10 ���� itoa
void itoa10(int n, char *buf);

using namespace Ogre;
using namespace std;

// ����� ���� Ŭ���� 
// << ��ü ���� >>
#include "cSingleton.h"
#include "CoreStorage.h"

// << ����ü >>
#include "StructData.h"

//// << �Ϲ� Ŭ���� >>
#include "Cam.h"
#include "SoundManager.h"
#include "LightManager.h"
#include "ModelManager.h"
#include "PostEffect.h"
#include "ListenerManager.h"
//#include "cShaderManager.h"
//#include "cMaterialManager.h"
//#include "cdrawManager.h"

