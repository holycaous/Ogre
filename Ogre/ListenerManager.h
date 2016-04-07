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
	OIS::InputManager* mInputManager;

	MainListener* mMainListener;
	KeyListener * mKeyListener;
public:
	void init()
	{
		// ������ �ʱ�ȭ
		size_t windowHnd = 0;
		std::ostringstream windowHndStr;
		OIS::ParamList pl;
		mCoreStorage->mWindow->getCustomAttribute("WINDOW", &windowHnd);
		windowHndStr << windowHnd;
		pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

		// ���� Ű���� �Ŵ��� ����
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

