#pragma once
class ModelManager : public cSingleton<ModelManager>
{
	CoreStorage* mCoreStorage = CoreStorage::getInstance();

	// 엔티티 & 씬노드
	std::vector<Entity*>    mEntityStorage;
	std::vector<SceneNode*> mSceneNode;

#ifdef DEBUG_MODE
	// 좌표계 전용
	Entity   * mAxis;
	SceneNode* mAxisNode;

	// 그리드 전용
	Ogre::ManualObject* gridPlane;
	Ogre::SceneNode   * gridPlaneNode;
	Ogre::MaterialPtr   gridPlaneMaterial;
#endif
public:
	void init()
	{
		// 리소스 초기화
		ResourceGroupManager::getSingleton().addResourceLocation("resource.zip", "Zip");
		ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

#ifdef DEBUG_MODE
		// 기본 매쉬 초기화
		_initDefaultMesh();
#endif
	}

	void clearClass()
	{

	}

	// 모델 클리어
	void clearModel()
	{
		// 불필요한 작업은 안하기 위해 검사.
		// 씬과 모델은 1:1 관계이므로, 뭐로 검사해도 상관없음.
		if (mEntityStorage.size() > 0)
		{
			// 그림자 끄기
			_resetShadow();

			// 버퍼 비우기
			mEntityStorage.clear();
			mSceneNode.clear();

			// 씬 클리어
			mCoreStorage->mSceneMgr->clearScene();

			// 기본 매쉬 다시 초기화
			_initDefaultMesh();
		}
	}

	// 모델 가져오기
	SceneNode* getModel(string _name)
	{
		return mCoreStorage->mRoot->getSceneManager("main")->getSceneNode(_name.c_str());
	}

	// 모델 추가
	void addModel(char* _objName, char* _meshName, float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
	{
		// 엔티티 & 노드 추가
		mEntityStorage.push_back(mCoreStorage->mSceneMgr->createEntity(_objName, _meshName));
		mSceneNode.push_back(mCoreStorage->mSceneMgr->getRootSceneNode()->createChildSceneNode(_objName, Vector3(_x, _y, _z)));
	}

	// 무작정 있는거 다 씬 셋팅
	void applyModel()
	{
#ifdef DEBUG_MODE
		// 그리드 표시
		gridPlaneNode->attachObject(gridPlane);

		// 좌표계 표시
		mAxisNode->attachObject(mAxis);
#endif
		// 각 씬에 각 오브젝트 붙이기 ( 1:1 관계 )
		for (unsigned int i = 0; i < mSceneNode.size(); ++i)
		{
			mSceneNode[i]->attachObject(mEntityStorage[i]);
		}

		// 그림자켜기
		_setShadow();
	}

private:

	// 그림자 켜기
	void _setShadow()
	{
		for (unsigned int i = 0; i < mEntityStorage.size(); ++i)
			mEntityStorage[i]->setCastShadows(true);
	}

	// 그림자 끄기
	void _resetShadow()
	{
		for (unsigned int i = 0; i < mEntityStorage.size(); ++i)
			mEntityStorage[i]->setCastShadows(false);
	}

#ifdef DEBUG_MODE
	// 기본 매쉬 초기화
	void _initDefaultMesh()
	{
		// 좌표계 매쉬 초기화
		_initAxis();

		// 엔진 그리드 초기화
		_initGrid();
	}

	// 좌표계 매쉬 초기화
	void _initAxis()
	{
		mAxis     = mCoreStorage->mSceneMgr->createEntity("Axis", "axes.mesh");
		mAxisNode = mCoreStorage->mSceneMgr->getRootSceneNode()->createChildSceneNode("Axis", Vector3(0.0f, 0.0f, 0.0f));
		mCoreStorage->mRoot->getSceneManager("main")->getSceneNode("Axis")->setScale(5, 5, 5);
	}

	// 그리드 초기화
	void _initGrid()
	{
		// 그리드 생성 & 노드에 등록
		gridPlane     = mCoreStorage->mSceneMgr->createManualObject("GridPlane");
		gridPlaneNode = mCoreStorage->mSceneMgr->getRootSceneNode()->createChildSceneNode("GridPlaneNode");

		// 재질 생성
		gridPlaneMaterial = Ogre::MaterialManager::getSingleton().create("GridPlanMaterial", "General");
		gridPlaneMaterial->setReceiveShadows(false);
		gridPlaneMaterial->getTechnique(0)->setLightingEnabled(true);
		gridPlaneMaterial->getTechnique(0)->getPass(0)->setDiffuse(1, 1, 1, 0);
		gridPlaneMaterial->getTechnique(0)->getPass(0)->setAmbient(1, 1, 1);
		gridPlaneMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(1, 1, 1);

		// 그리드 좌표 찍기
		gridPlane->begin("GridPlaneMaterial", Ogre::RenderOperation::OT_LINE_LIST);

		for (int i = 0; i < 21; i++)
		{
			gridPlane->position(-500.0f, 0.0f, 500.0f - i * 50);
			gridPlane->position(500.0f, 0.0f, 500.0f - i * 50);

			gridPlane->position(-500.f + i * 50, 0.f, 500.0f);
			gridPlane->position(-500.f + i * 50, 0.f, -500.f);
		}

		gridPlane->end();
	}
#endif
};

