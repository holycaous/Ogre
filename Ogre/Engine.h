#pragma once
#include "GameStateManager.h"

// ������ �۵� Ŭ������ <<------------------------ ���� ��ƾ��ҵ� @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
class ESCListener : public FrameListener {
	OIS::Keyboard *mKeyboard;

public:
	ESCListener(OIS::Keyboard *keyboard) : mKeyboard(keyboard) {}
	bool frameStarted(const FrameEvent &evt)
	{
		mKeyboard->capture();
		return !mKeyboard->isKeyDown(OIS::KC_ESCAPE);
	}
};


class MainListener : public FrameListener {
	OIS::Keyboard *mKeyboard;
	Root* mRoot;
	SceneNode *mProfessorNode, *mNinjaNode;

public:
	MainListener(Root* root, OIS::Keyboard *keyboard) : mKeyboard(keyboard), mRoot(root)
	{
		mProfessorNode = mRoot->getSceneManager("main")->getSceneNode("Professor");
		mNinjaNode = mRoot->getSceneManager("main")->getSceneNode("Ninja");
	}

	bool frameStarted(const FrameEvent &evt)
	{
		// Fill Here ------------------------------------------------------------------------------


		// -----------------------------------------------------------------------------------------

		static float ninjaVelocity = 100.0f;

		if (mNinjaNode->getPosition().x < -400.f || mNinjaNode->getPosition().x > 400.0f)
			ninjaVelocity *= -1;
		mNinjaNode->translate(ninjaVelocity * evt.timeSinceLastFrame, 0, 0);

		return true;
	}

};

class Engine
{
	GameStateManager* mGameStateManager;

	Root* mRoot;
	RenderWindow* mWindow;
	SceneManager* mSceneMgr;
	Camera* mCamera;
	Viewport* mViewport;
	OIS::Keyboard* mKeyboard;
	OIS::InputManager *mInputManager;

	MainListener* mMainListener;
	ESCListener* mESCListener;

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
	}

	void init()
	{
		// ���� ���� �ʱ�ȭ
		GameStateManager::getInstance()->init();
		mGameStateManager = GameStateManager::getInstance();
	}

	void update(float& dt)
	{
		// �� ������Ʈ ������Ʈ
		mGameStateManager->update(dt);
	}

	void draw()
	{
		// �ؿ��� �� ������ ��ġ�ؾ���
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

		// OGRE�� ���� ��Ʈ ������Ʈ ����
#if !defined(_DEBUG)
		mRoot = new Root("plugins.cfg", "ogre.cfg", "ogre.log");
#else
		mRoot = new Root("plugins_d.cfg", "ogre.cfg", "ogre.log");
#endif


		// �ʱ� ������ ���ǱԷ��̼� ���� - ogre.cfg �̿�
		if (!mRoot->restoreConfig()) {
			if (!mRoot->showConfigDialog()) return;
		}

		mWindow = mRoot->initialise(true, "Moving Professor & Ninja : Copyleft by Dae-Hyun Lee");


		// ESC key�� ������ ���, ����� ���� ������ ������ Ż���� ó��
		size_t windowHnd = 0;
		std::ostringstream windowHndStr;
		OIS::ParamList pl;
		mWindow->getCustomAttribute("WINDOW", &windowHnd);
		windowHndStr << windowHnd;
		pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
		mInputManager = OIS::InputManager::createInputSystem(pl);
		mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, false));


		mSceneMgr = mRoot->createSceneManager(ST_GENERIC, "main");
		mCamera = mSceneMgr->createCamera("main");


		mCamera->setPosition(0.0f, 100.0f, 500.0f);
		mCamera->lookAt(0.0f, 100.0f, 0.0f);

		mCamera->setNearClipDistance(5.0f);

		mViewport = mWindow->addViewport(mCamera);
		mViewport->setBackgroundColour(ColourValue(0.0f, 0.0f, 0.5f));
		mCamera->setAspectRatio(Real(mViewport->getActualWidth()) / Real(mViewport->getActualHeight()));


		ResourceGroupManager::getSingleton().addResourceLocation("resource.zip", "Zip");
		ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

		mSceneMgr->setAmbientLight(ColourValue(1.0f, 1.0f, 1.0f));

		// ��ǥ�� ǥ��
		Ogre::Entity* mAxesEntity = mSceneMgr->createEntity("Axes", "axes.mesh");
		mSceneMgr->getRootSceneNode()->createChildSceneNode("AxesNode", Ogre::Vector3(0, 0, 0))->attachObject(mAxesEntity);
		mSceneMgr->getSceneNode("AxesNode")->setScale(5, 5, 5);

		_drawGridPlane();



		Entity* entity1 = mSceneMgr->createEntity("Professor", "DustinBody.mesh");
		Entity* entity2 = mSceneMgr->createEntity("Ninja", "ninja.mesh");


		SceneNode* node1 = mSceneMgr->getRootSceneNode()->createChildSceneNode("Professor", Vector3(0.0f, 0.0f, 0.0f));
		node1->attachObject(entity1);

		SceneNode* node2 = mSceneMgr->getRootSceneNode()->createChildSceneNode("Ninja", Vector3(200.0f, 0.0f, -200.0f));
		node2->attachObject(entity2);



		mESCListener = new ESCListener(mKeyboard);
		mRoot->addFrameListener(mESCListener);

		mMainListener = new MainListener(mRoot, mKeyboard);
		mRoot->addFrameListener(mMainListener);


		mRoot->startRendering();

		mInputManager->destroyInputObject(mKeyboard);
		OIS::InputManager::destroyInputSystem(mInputManager);

		delete mRoot;



		// �� ������Ʈ �׸���
		mGameStateManager->draw();
	}

	void clearClass()
	{

	}

private:
	// �׸��� �׸���
	void _drawGridPlane(void)
	{
		Ogre::ManualObject* gridPlane  = mSceneMgr->createManualObject("GridPlane");
		Ogre::SceneNode* gridPlaneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("GridPlaneNode");

		Ogre::MaterialPtr gridPlaneMaterial = Ogre::MaterialManager::getSingleton().create("GridPlanMaterial", "General");
		gridPlaneMaterial->setReceiveShadows(false);
		gridPlaneMaterial->getTechnique(0)->setLightingEnabled(true);
		gridPlaneMaterial->getTechnique(0)->getPass(0)->setDiffuse(1, 1, 1, 0);
		gridPlaneMaterial->getTechnique(0)->getPass(0)->setAmbient(1, 1, 1);
		gridPlaneMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(1, 1, 1);

		gridPlane->begin("GridPlaneMaterial", Ogre::RenderOperation::OT_LINE_LIST);
		for (int i = 0; i < 21; i++)
		{
			gridPlane->position(-500.0f, 0.0f, 500.0f - i * 50);
			gridPlane->position(500.0f, 0.0f, 500.0f - i * 50);

			gridPlane->position(-500.f + i * 50, 0.f, 500.0f);
			gridPlane->position(-500.f + i * 50, 0.f, -500.f);
		}

		gridPlane->end();

		gridPlaneNode->attachObject(gridPlane);
	}
};

