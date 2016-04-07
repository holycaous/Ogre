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

	// 키보드 업
	bool keyPressed(const OIS::KeyEvent &e)
	{
		return true;
	}

	// 키보드 다운
	bool keyReleased(const OIS::KeyEvent &e)
	{
		return true;
	}
};

// 마우스 매니저
class MouseListener : public FrameListener
{
	OIS::Mouse       * mMouse;
	OIS::InputManager* mPos;
	OIS::MouseState  * mState;

public:
	void init(OIS::Mouse* mouse)
	{
		mMouse = mouse;
	}
	bool frameStarted(const FrameEvent &evt)
	{
		// 키 캡쳐
		mMouse->capture();

		//// 마우스 위치
		//mPos = mMouse->getCreator();

		//// 마우스 상태
		//mState = mMouse->getMouseState();

		return true;
	}

	// 마우스 다운
	bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
	{
		return true;
	}

	// 마우스 업
	bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
	{
		return true;
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
	OIS::Mouse       * mMouse;
	OIS::InputManager* mInputManager;

	MainListener * mMainListener;
	KeyListener  * mKeyListener;
	MouseListener* mMouseListener;
public:
	void init()
	{
		// 리스너 초기화
		_initDefault();

		//-----------------------------------------------------------------------------//
		// 매니저 등록
		//-----------------------------------------------------------------------------//

		// KeyListener
		mKeyListener = new KeyListener;
		mKeyListener->init(mKeyboard);
		mCoreStorage->mRoot->addFrameListener(mKeyListener);

		// MouseListener
		mMouseListener = new MouseListener;
		mMouseListener->init(mMouse);
		mCoreStorage->mRoot->addFrameListener(mMouseListener);

		// MainListener
		mMainListener = new MainListener;
		mCoreStorage->mRoot->addFrameListener(mMainListener);

		//-----------------------------------------------------------------------------//
	}

	void clearClass()
	{
		mInputManager->destroyInputObject(mKeyboard);
		mInputManager->destroyInputObject(mMouse);
		OIS::InputManager::destroyInputSystem(mInputManager);
	}

private:
	// 리스너 초기화
	void _initDefault()
	{
		// 리스너 초기화
		size_t windowHnd = 0;
		std::ostringstream windowHndStr;
		OIS::ParamList pl;
		mCoreStorage->mWindow->getCustomAttribute("WINDOW", &windowHnd);
		windowHndStr << windowHnd;
		pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
		mInputManager = OIS::InputManager::createInputSystem(pl);

		// 엔진 키보드 매니저 생성
		mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, false));

		// 엔진 마우스 매니저 생성
		mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));

	}
};

