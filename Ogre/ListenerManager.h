#pragma once
#include "GameStateManager.h"

// Ű���� �Ŵ���
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
		// Ű ĸ��
		mKeyboard->capture();

		// �������� ����
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

		// ESC Ű ����
		return !mKeyboard->isKeyDown(OIS::KC_ESCAPE);
	}

	// Ű���� ��
	bool keyPressed(const OIS::KeyEvent &e)
	{
		return true;
	}

	// Ű���� �ٿ�
	bool keyReleased(const OIS::KeyEvent &e)
	{
		return true;
	}
};

// ���콺 �Ŵ���
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
		// Ű ĸ��
		mMouse->capture();

		//// ���콺 ��ġ
		//mPos = mMouse->getCreator();

		//// ���콺 ����
		//mState = mMouse->getMouseState();

		return true;
	}

	// ���콺 �ٿ�
	bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
	{
		return true;
	}

	// ���콺 ��
	bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
	{
		return true;
	}
};

// ������Ʈ ������Ʈ ��
class MainListener : public FrameListener
{
	GameStateManager* mGameStateManager = GameStateManager::getInstance();

public:
	bool frameStarted(const FrameEvent &evt)
	{
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
	// ������ �ʱ�ȭ
	void _initDefault()
	{
		// ������ �ʱ�ȭ
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

		// ���� Ű���� �Ŵ��� ����
		mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, false));

		// ���� ���콺 �Ŵ��� ����
		mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));

	}
};

