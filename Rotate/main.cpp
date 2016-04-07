#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#include <Ogre.h>
#include <OIS/OIS.h>


using namespace Ogre;


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
  SceneNode *mProfessorNode, *mFishNode;

public:
  MainListener(Root* root, OIS::Keyboard *keyboard) : mKeyboard(keyboard), mRoot(root) 
  {
    mProfessorNode = mRoot->getSceneManager("main")->getSceneNode("Professor");
    mFishNode = mRoot->getSceneManager("main")->getSceneNode("Fish");
  }

  bool frameStarted(const FrameEvent &evt)
  {
    // Fill Here ----------------------------------------------

	  static SceneNode *curNode = mProfessorNode;

	  if (mKeyboard->isKeyDown(OIS::KC_P))
		  curNode->pitch(Degree(1.0f));
	  else if (mKeyboard->isKeyDown(OIS::KC_Y))
		  curNode->yaw(Degree(1.0f));
	  else if (mKeyboard->isKeyDown(OIS::KC_R))
		  curNode->roll(Degree(1.0f));
	  else if (mKeyboard->isKeyDown(OIS::KC_1))
		  curNode = mProfessorNode;
	  else if (mKeyboard->isKeyDown(OIS::KC_2))
		  curNode = mFishNode;

    // --------------------------------------------------------

	
	// ��� �ȱ�
	static float roate =  0;
	static int rSwitch = -1;

	static float ninjaVelocity = 100.0f;

	if (curNode->getPosition().z < -250.f || curNode->getPosition().z > 250.0f)
	{
		rSwitch = 0;
		ninjaVelocity *= -1;
	}

	curNode->translate(0, 0, ninjaVelocity * evt.timeSinceLastFrame);

	// ȸ��
	switch (rSwitch)
	{
		case 0:
			if (roate >= 180)
				++rSwitch;
			
			// ȸ���Ѵ�
			roate += 0.5f;
			curNode->yaw(Degree(0.5f), Node::TS_LOCAL);
			break;

		case 1:
			roate = 0.0f;
			rSwitch = -1;
			break;

		default:
			break;
	}

	

	// ���� ȸ��
	Vector3 moveMent(0.0f, 0.0f, 100.0f);

	mFishNode->translate(-moveMent, Node::TS_LOCAL);
	mFishNode->yaw(Degree(1.0f), Node::TS_LOCAL);
	mFishNode->translate(moveMent, Node::TS_LOCAL);

    return true;
  }

};

class LectureApp {

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

  LectureApp() {}

  ~LectureApp() {}

  void go(void)
  {
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

    mWindow = mRoot->initialise(true, "Rotate : Copyleft by Dae-Hyun Lee");


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


    //mCamera->setPosition(0.0f, 100.0f, 700.0f);
	mCamera->setPosition(0.0f, 500.0f, 700.0f);
	mCamera->lookAt(0.0f, 0.0f, 0.0f);

    mCamera->setNearClipDistance(5.0f);

    mViewport = mWindow->addViewport(mCamera);
    mViewport->setBackgroundColour(ColourValue(0.0f,0.0f,0.5f));
    mCamera->setAspectRatio(Real(mViewport->getActualWidth()) / Real(mViewport->getActualHeight()));


    ResourceGroupManager::getSingleton().addResourceLocation("resource.zip", "Zip");
	ResourceGroupManager::getSingleton().addResourceLocation("fish.zip", "Zip");
    ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    mSceneMgr->setAmbientLight(ColourValue(1.0f, 1.0f, 1.0f));

    // ��ǥ�� ǥ��
    Ogre::Entity* mAxesEntity = mSceneMgr->createEntity("Axes", "axes.mesh");
    mSceneMgr->getRootSceneNode()->createChildSceneNode("AxesNode",Ogre::Vector3(0,0,0))->attachObject(mAxesEntity);
    mSceneMgr->getSceneNode("AxesNode")->setScale(5, 5, 5);

    _drawGridPlane();


    Entity* entity1 = mSceneMgr->createEntity("Professor", "DustinBody.mesh");
    SceneNode* node1 = mSceneMgr->getRootSceneNode()->createChildSceneNode("Professor", Vector3(0.0f, 0.0f, 0.0f));
    node1->attachObject(entity1);

    Entity* entity2 = mSceneMgr->createEntity("Fish", "fish.mesh");
    SceneNode* node2 = node1->createChildSceneNode("Fish", Vector3(0.0f, 0.0f, 100.0f));
    node2->attachObject(entity2);
	node2->setScale(5.0f, 5.0f, 5.0f);
	node2->setInheritOrientation(false);

    mESCListener =new ESCListener(mKeyboard);
    mRoot->addFrameListener(mESCListener);

    mMainListener = new MainListener(mRoot, mKeyboard);
    mRoot->addFrameListener(mMainListener);



    mRoot->startRendering();

    mInputManager->destroyInputObject(mKeyboard);
    OIS::InputManager::destroyInputSystem(mInputManager);

    delete mRoot;
  }

private:
  void _drawGridPlane(void)
  {
    Ogre::ManualObject* gridPlane =  mSceneMgr->createManualObject("GridPlane"); 
    Ogre::SceneNode* gridPlaneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("GridPlaneNode"); 

    Ogre::MaterialPtr gridPlaneMaterial = Ogre::MaterialManager::getSingleton().create("GridPlanMaterial","General"); 
    gridPlaneMaterial->setReceiveShadows(false); 
    gridPlaneMaterial->getTechnique(0)->setLightingEnabled(true); 
    gridPlaneMaterial->getTechnique(0)->getPass(0)->setDiffuse(1,1,1,0); 
    gridPlaneMaterial->getTechnique(0)->getPass(0)->setAmbient(1,1,1); 
    gridPlaneMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(1,1,1); 

    gridPlane->begin("GridPlaneMaterial", Ogre::RenderOperation::OT_LINE_LIST); 
    for(int i=0; i<21; i++)
    {
      gridPlane->position(-500.0f, 0.0f, 500.0f-i*50);
      gridPlane->position(500.0f, 0.0f, 500.0f-i*50);

      gridPlane->position(-500.f+i*50, 0.f, 500.0f);
      gridPlane->position(-500.f+i*50, 0.f, -500.f);
    }

    gridPlane->end(); 

    gridPlaneNode->attachObject(gridPlane);
  }
};


#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
  INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
  int main(int argc, char *argv[])
#endif
  {
    LectureApp app;

    try {

      app.go();

    } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
      MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
      std::cerr << "An exception has occured: " <<
        e.getFullDescription().c_str() << std::endl;
#endif
    }

    return 0;
  }

#ifdef __cplusplus
}
#endif
