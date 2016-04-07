#pragma once
#include "GameStateManager.h"

class Engine
{
	// �Ŵ����� Ŭ������
	GameStateManager* mGameStateManager = GameStateManager::getInstance();
	ListenerManager * mListenerManager  = ListenerManager ::getInstance();
	ModelManager    * mModelManager     = ModelManager    ::getInstance();
	Cam			    * mCam			    = Cam			  ::getInstance();

	// �Ű� ����
	Root        * mRoot;
	RenderWindow* mWindow;
	SceneManager* mSceneMgr;
	
	// ����
	string mGameName = "�̹��� �ٿ�������";

public:
	Engine()
	{

	}

	~Engine()
	{
		//------------------------------------------------------//
		// �̱��� Ŭ������ ����
		//------------------------------------------------------//
		// ������Ʈ ���� ���� ����
		GameStateSave::destroyInstance();

		// ���� ���� �Ŵ��� ����
		GameStateManager::getInstance()->clearClass();
		GameStateManager::destroyInstance();

		// �� �Ŵ���
		ModelManager::getInstance()->clearClass();
		ModelManager::destroyInstance();

		// �� �Ŵ���
		Cam::getInstance()->clearClass();
		Cam::destroyInstance();

		// ����Ʈ �Ŵ���
		LightManager::getInstance()->clearClass();
		LightManager::destroyInstance();

		// ������ �Ŵ���
		ListenerManager::getInstance()->clearClass();
		ListenerManager::destroyInstance();

		// �ھ� ���丮��
		CoreStorage::destroyInstance();
	}

	void init()
	{
		// ���ſ��� �ʱ�ȭ
		_initEngine();

		// ���� �ʱ�ȭ
		_initGame();
	}

	void draw()
	{
		// �� ������Ʈ �׸���
		mGameStateManager->draw();

		// ��ü ��� ( �ø��� )
		mRoot->startRendering();
	}

	void clearClass()
	{
		delete mRoot;
	}

private:
	// ���� �ʱ�ȭ
	void _initEngine()
	{
		// OGRE�� ���� ��Ʈ ������Ʈ ����
#if !defined(_DEBUG)
		mRoot = new Root("plugins.cfg", "ogre.cfg", "ogre.log");
#else
		mRoot = new Root("plugins_d.cfg", "ogre.cfg", "ogre.log");
#endif

		// �ʱ� ������ ���ǱԷ��̼� ���� - ogre.cfg �̿�
		if (!mRoot->restoreConfig()) 
		{
			// ���ǱԷ��̼� ���̾�α׸� ����Ѵ�.
			if (!mRoot->showConfigDialog()) 
				return;
		}

		// ������ �ʱ�ȭ
		mWindow = mRoot->initialise(true, mGameName.c_str());
	}

	// ���� �ʱ�ȭ
	void _initGame()
	{
		// �� ��� �ʱ�ȭ
		mSceneMgr = mRoot->createSceneManager(ST_GENERIC, "main");

		// �ھ� ���丮�� �ʱ�ȭ
		_initCoreStorage();
		
		// ī�޶� �ʱ�ȭ
		mCam->init();

		// �� �Ŵ��� �ʱ�ȭ
		mModelManager->init();

		// ���� ���� �ʱ�ȭ
		mGameStateManager->init();

		// ������ �ʱ�ȭ
		mListenerManager->init();
	}

	// �ھ� ���丮�� �ʱ�ȭ 
	void _initCoreStorage()
	{
		CoreStorage::getInstance()->mRoot     = mRoot;
		CoreStorage::getInstance()->mWindow   = mWindow;
		CoreStorage::getInstance()->mSceneMgr = mSceneMgr;
	}
};

