#pragma once
#include "GameStateManager.h"

// 키보드 매니저
class KeyListener : public FrameListener, public OIS::KeyListener
{
	Cam* mCam = Cam::getInstance();

	OIS::Keyboard* mKeyboard;
public:
	void init(OIS::Keyboard* keyboard)
	{
		mKeyboard = keyboard;
	}

	bool frameStarted(const FrameEvent &evt)
	{
		if (mKeyboard->isKeyDown(OIS::KC_ESCAPE))
		{
			return false;
		}
		else if (mKeyboard->isKeyDown(OIS::KC_W))
		{
			mCam->SetZ(-250.0f);
		}
		else if (mKeyboard->isKeyDown(OIS::KC_S))
		{
			mCam->SetZ(250.0f);
		}
		else if (mKeyboard->isKeyDown(OIS::KC_A))
		{
			mCam->SetX(-250.0f);
		}
		else if (mKeyboard->isKeyDown(OIS::KC_D))
		{
			mCam->SetX(250.0f);
		}
			
		return true;
	}

	// 키보드 다운
	bool keyPressed(const OIS::KeyEvent &e)
	{
		switch (e.key)
		{
		case OIS::KC_1:
			GameStateSave::getInstance()->stateChangeCheck = true;
			GameStateSave::getInstance()->stateChaneNumber = e_MainState;
			break;
		case OIS::KC_2:
			GameStateSave::getInstance()->stateChangeCheck = true;
			GameStateSave::getInstance()->stateChaneNumber = e_PlayState;
			break;

		default:
			break;
		}
		return true;
	}

	// 키보드 업
	bool keyReleased(const OIS::KeyEvent &e)
	{
		return true;
	}
};

// 마우스 매니저
class MouseListener : public OIS::MouseListener
{
	Cam* mCam = Cam::getInstance();
	bool mDown = false;
public:
	// 마우스 이동
	bool mouseMoved(const OIS::MouseEvent &e)
	{
		if (mDown)
		{
			mCam->RotateX(e);
			mCam->RotateY(e);
		}
		return true;
	}

	// 마우스 다운
	bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
	{
		mDown = true;
		return true;
	}

	// 마우스 업
	bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
	{
		mDown = false;
		return true;
	}
};

// 스테이트 업데이트 용
class MainListener : public FrameListener
{
	GameStateManager* mGameStateManager = GameStateManager::getInstance();
	CoreStorage     * mCoreStorage      = CoreStorage     ::getInstance();
	Cam             * mCam              = Cam             ::getInstance();

	// 리스너 업데이트용
	OIS::Keyboard   * mKeyboard;
	OIS::Mouse      * mMouse;
public:
	void init(OIS::Keyboard* keyboard, OIS::Mouse* mouse)
	{
		mKeyboard = keyboard;
		mMouse    = mouse;
	}

	bool frameStarted(const FrameEvent &evt)
	{
		// 키보드, 마우스 캡쳐
		mKeyboard->capture();
		mMouse   ->capture();

		// 카메라 업데이트
		mCam->Update(evt.timeSinceLastFrame);

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

		// MainListener
		mMainListener = new MainListener;
		mMainListener->init(mKeyboard, mMouse);
		mCoreStorage->mRoot->addFrameListener(mMainListener);

		// KeyListener
		mKeyListener = new KeyListener;
		mKeyListener->init(mKeyboard);
		mKeyboard->setEventCallback(mKeyListener);
		mCoreStorage->mRoot->addFrameListener(mKeyListener);

		// MouseListener
		mMouseListener = new MouseListener;
		mMouse->setEventCallback(mMouseListener);


		//-----------------------------------------------------------------------------//
	}

	void clearClass()
	{
		mInputManager->destroyInputObject(mKeyboard);
		mInputManager->destroyInputObject(mMouse);
		OIS::InputManager::destroyInputSystem(mInputManager);

		delete mKeyListener;
		delete mMouseListener;
		delete mMainListener;
	}

private:
	// 리스너 초기화
	void _initDefault()
	{
		// 리스너 초기화
		size_t windowHnd = 0;
		std::ostringstream windowHndStr;
		mCoreStorage->mWindow->getCustomAttribute("WINDOW", &windowHnd);
		windowHndStr << windowHnd;

		// 파라미터 리스트
		OIS::ParamList pl;
		pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));

		// 엔진 인풋 매니저 생성
		mInputManager = OIS::InputManager::createInputSystem(pl);

		// 엔진 키보드 매니저 생성
		mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));

		// 엔진 마우스 매니저 생성
		mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));

	}
};

