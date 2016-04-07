#pragma once
#include "GameStateManager.h"

// Ű���� �Ŵ���
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

	// Ű���� �ٿ�
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

	// Ű���� ��
	bool keyReleased(const OIS::KeyEvent &e)
	{
		return true;
	}
};

// ���콺 �Ŵ���
class MouseListener : public OIS::MouseListener
{
	Cam* mCam = Cam::getInstance();
	bool mDown = false;
public:
	// ���콺 �̵�
	bool mouseMoved(const OIS::MouseEvent &e)
	{
		if (mDown)
		{
			mCam->RotateX(e);
			mCam->RotateY(e);
		}
		return true;
	}

	// ���콺 �ٿ�
	bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
	{
		mDown = true;
		return true;
	}

	// ���콺 ��
	bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
	{
		mDown = false;
		return true;
	}
};

// ������Ʈ ������Ʈ ��
class MainListener : public FrameListener
{
	GameStateManager* mGameStateManager = GameStateManager::getInstance();
	CoreStorage     * mCoreStorage      = CoreStorage     ::getInstance();
	Cam             * mCam              = Cam             ::getInstance();

	// ������ ������Ʈ��
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
		// Ű����, ���콺 ĸ��
		mKeyboard->capture();
		mMouse   ->capture();

		// ī�޶� ������Ʈ
		mCam->Update(evt.timeSinceLastFrame);

		// �� ������Ʈ ������Ʈ
		mGameStateManager->update(evt.timeSinceLastFrame);

		return true;
	}
};

// ������ �Ŵ���
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
		// ������ �ʱ�ȭ
		_initDefault();

		//-----------------------------------------------------------------------------//
		// �Ŵ��� ���
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
	// ������ �ʱ�ȭ
	void _initDefault()
	{
		// ������ �ʱ�ȭ
		size_t windowHnd = 0;
		std::ostringstream windowHndStr;
		mCoreStorage->mWindow->getCustomAttribute("WINDOW", &windowHnd);
		windowHndStr << windowHnd;

		// �Ķ���� ����Ʈ
		OIS::ParamList pl;
		pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));

		// ���� ��ǲ �Ŵ��� ����
		mInputManager = OIS::InputManager::createInputSystem(pl);

		// ���� Ű���� �Ŵ��� ����
		mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));

		// ���� ���콺 �Ŵ��� ����
		mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));

	}
};

