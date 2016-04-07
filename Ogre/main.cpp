#include "stdafx.h"
#include "Engine.h"

// 메인
#ifdef __cplusplus
extern "C" 
{
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
  INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
  int main(int argc, char *argv[])
#endif
  {
	Engine engine;
	// 엔진 초기화
	engine.init();

	// 예외 잡기
    try 
	{
		engine.draw();
    } 

	// 예외 처리
	catch( Ogre::Exception& e ) 
	{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
      MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
      std::cerr << "An exception has occured: " <<
        e.getFullDescription().c_str() << std::endl;
#endif
    }

	// 엔진 삭제
	engine.clearClass();
    return 0;
  }
#ifdef __cplusplus
}
#endif

