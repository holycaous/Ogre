#pragma once
#include "GameStateManager.h"

class Engine
{
	// �Ŵ����� Ŭ������
	GameStateManager* mGameStateManager = GameStateManager::getInstance();
	ListenerManager * mListenerManager  = ListenerManager ::getInstance();
	ModelManager    * mModelManager     = ModelManager    ::getInstance();
	Cam			    * mCam			    = Cam			  ::getInstance();
	LightManager    * mLightManager     = LightManager    ::getInstance();
	PostEffect      * mPostEffect       = PostEffect      ::getInstance();
	SoundManager    * mSoundManager     = SoundManager    ::getInstance();

	// �Ű� ����
	Root        * mRoot;
	RenderWindow* mWindow;
	SceneManager* mSceneMgr;
	
	// ����
	string mGameName = "�̹��� �ٿ�������";

public:
	Engine()
	{
		// ���� �ʱ�ȭ
		init();
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

		// ����Ʈ ����Ʈ �Ŵ���
		PostEffect::getInstance()->clearClass();
		PostEffect::destroyInstance();

		// ���� �Ŵ���
		SoundManager::getInstance()->clearClass();
		SoundManager::destroyInstance();

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
		// �� ������Ʈ �� ����
		//mGameStateManager->setScene();

		// ��ü ��� ( �ø��� )
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

		// �� ��� �ʱ�ȭ
		mSceneMgr = mRoot->createSceneManager(ST_GENERIC, "main");
	}

	// ���� �ʱ�ȭ
	void _initGame()
	{
		// �ھ� ���丮�� �ʱ�ȭ(���� �߿亯���� ������ ���밴ü)
		_initCoreStorage();

		// ���� �Ŵ��� �ʱ�ȭ
		mSoundManager->init();

		// ����Ʈ ����Ʈ �ʱ�ȭ
		mPostEffect->init();
		
		// ī�޶� �ʱ�ȭ
		mCam->init();

		// ����Ʈ �ʱ�ȭ
		mLightManager->init();

		// �� �Ŵ��� �ʱ�ȭ
		mModelManager->init();
		
		// ����Ʈ ����Ʈ �ʱ�ȭ2
		mPostEffect->setoverlay();

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

