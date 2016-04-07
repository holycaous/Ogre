#pragma once
#include "GameStateManager.h"

// 키보드 매니저
class KeyListener : public FrameListener
{
	OIS::Keyboard *mKeyboard;

public:
	void init(OIS::Keyboard *keyboard)
	{
		mKeyboard = keyboard;
	}
	bool frameStarted(const FrameEvent &evt)
	{
		// 키 캡쳐
		mKeyboard->capture();

		// 스테이지 변경
		if (mKeyboard->isKeyDown(OIS::KC_1))
		{
			GameStateSave::getInstance()->stateChangeCheck = true;
			GameStateSave::getInstance()->stateChaneNumber = e_MainState;
		}
		else if (mKeyboard->isKeyDown(OIS::KC_2))
		{
			GameStateSave::getInstance()->stateChangeCheck = true;
			GameStateSave::getInstance()->stateChaneNumber = e_PlayState;
		}

		// ESC 키 유무
		return !mKeyboard->isKeyDown(OIS::KC_ESCAPE);
	}
};

// 스테이트 업데이트 용
class MainListener : public FrameListener 
{
	GameStateManager* mGameStateManager = GameStateManager::getInstance();

public:
	bool frameStarted(const FrameEvent &evt)
	{
		// 각 스테이트 업데이트
		mGameStateManager->update(evt.timeSinceLastFrame);
		return true;
	}
};

// 리스너 매니저
class ListenerManager : public cSingleton<ListenerManager>
{
	CoreStorage* mCoreStorage = CoreStorage::getInstance();

	OIS::Keyboard    * mKeyboard;
	OIS::InputManager* mInputManager;

	MainListener* mMainListener;
	KeyListener * mKeyListener;
public:
	void init()
	{
		// 리스너 초기화
		size_t windowHnd = 0;
		std::ostringstream windowHndStr;
		OIS::ParamList pl;
		mCoreStorage->mWindow->getCustomAttribute("WINDOW", &windowHnd);
		windowHndStr << windowHnd;
		pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

		// 엔진 키보드 매니저 생성
		mInputManager = OIS::InputManager::createInputSystem(pl);
		mKeyboard     = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, false));

		//-----------------------------------------------------------------------------//

		// KeyListener
		mKeyListener = new KeyListener;
		mKeyListener->init(mKeyboard);
		mCoreStorage->mRoot->addFrameListener(mKeyListener);

		// MainListener
		mMainListener = new MainListener;
		mCoreStorage->mRoot->addFrameListener(mMainListener);

		//-----------------------------------------------------------------------------//
	}

	void clearClass()
	{
		mInputManager->destroyInputObject(mKeyboard);
		OIS::InputManager::destroyInputSystem(mInputManager);
	}
};

