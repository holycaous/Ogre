#pragma once
#include "GameStateManager.h"

class Engine
{
	// 매니저급 클래스들
	GameStateManager* mGameStateManager = GameStateManager::getInstance();
	ListenerManager * mListenerManager  = ListenerManager ::getInstance();
	ModelManager    * mModelManager     = ModelManager    ::getInstance();
	Cam			    * mCam			    = Cam			  ::getInstance();

	// 매개 변수
	Root        * mRoot;
	RenderWindow* mWindow;
	SceneManager* mSceneMgr;
	
	// 제목
	string mGameName = "이번엔 핵엔슬래시";

public:
	Engine()
	{

	}

	~Engine()
	{
		//------------------------------------------------------//
		// 싱글톤 클래스들 제거
		//------------------------------------------------------//
		// 스테이트 상태 변수 제거
		GameStateSave::destroyInstance();

		// 게임 상태 매니저 제거
		GameStateManager::getInstance()->clearClass();
		GameStateManager::destroyInstance();

		// 모델 매니저
		ModelManager::getInstance()->clearClass();
		ModelManager::destroyInstance();

		// 모델 매니저
		Cam::getInstance()->clearClass();
		Cam::destroyInstance();

		// 라이트 매니저
		LightManager::getInstance()->clearClass();
		LightManager::destroyInstance();

		// 리스너 매니저
		ListenerManager::getInstance()->clearClass();
		ListenerManager::destroyInstance();

		// 코어 스토리지
		CoreStorage::destroyInstance();
	}

	void init()
	{
		// 오거엔진 초기화
		_initEngine();

		// 게임 초기화
		_initGame();
	}

	void draw()
	{
		// 각 스테이트 그리기
		//mGameStateManager->draw();

		// 전체 출력 ( 플리핑 )
		mRoot->startRendering();
	}

	void clearClass()
	{
		delete mRoot;
	}

	bool frameStared(const FrameEvent& ent)
	{

	}

	bool frameEnded(const FrameEvent& ent)
	{

	}
private:
	// 엔진 초기화
	void _initEngine()
	{
		// OGRE의 메인 루트 오브젝트 생성
#if !defined(_DEBUG)
		mRoot = new Root("plugins.cfg", "ogre.cfg", "ogre.log");
#else
		mRoot = new Root("plugins_d.cfg", "ogre.cfg", "ogre.log");
#endif

		// 초기 시작의 컨피규레이션 설정 - ogre.cfg 이용
		if (!mRoot->restoreConfig()) 
		{
			// 컨피규레이션 다이얼로그를 출력한다.
			if (!mRoot->showConfigDialog()) 
				return;
		}

		// 윈도우 초기화
		mWindow = mRoot->initialise(true, mGameName.c_str());
	}

	// 게임 초기화
	void _initGame()
	{
		// 씬 노드 초기화
		mSceneMgr = mRoot->createSceneManager(ST_GENERIC, "main");

		// 코어 스토리지 초기화
		_initCoreStorage();
		
		// 카메라 초기화
		mCam->init();

		// 모델 매니저 초기화
		mModelManager->init();

		// 게임 상태 초기화
		mGameStateManager->init();

		// 리스너 초기화
		mListenerManager->init();
	}

	// 코어 스토리지 초기화 
	void _initCoreStorage()
	{
		CoreStorage::getInstance()->mRoot     = mRoot;
		CoreStorage::getInstance()->mWindow   = mWindow;
		CoreStorage::getInstance()->mSceneMgr = mSceneMgr;
	}
};

