#pragma once
class ModelManager : public cSingleton<ModelManager>
{
	CoreStorage* mCoreStorage = CoreStorage::getInstance();

	// 엔티티 & 씬노드
	std::map<string, Model> mObjectStorage;

	// 플레이어 지정
	string mPlayerName;

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
		ResourceGroupManager::getSingleton().addResourceLocation("./", "FileSystem");
		ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

#ifdef DEBUG_MODE
		// 기본 매쉬 초기화
		_initDefaultMesh();
#endif
	}

	void clearClass()
	{
		// 버퍼 비우기
		mObjectStorage.clear();
	}

	// 모델 클리어
	void clearModel()
	{
		// 불필요한 작업은 안하기 위해 검사.
		if (mObjectStorage.size() > 0)
		{
			// 버퍼 비우기
			mObjectStorage.clear();

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
	void addModel(string _objName, string _meshDataName, float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
	{
		// 모델 임시 저장공간
		Model tModel;

		// 모델 초기화
		tModel.initModel(_objName, _meshDataName, _x, _y, _z);

		// 모델 저장
		mObjectStorage[_objName] = tModel;
	}

	// 애니메이션 추가
	void addAni(string _objName, string _aniName)
	{
		mObjectStorage[_objName].initAni(_objName, _aniName);
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
		// 입력된 정보들을, 각 모델에 적용
		for (auto itor = mObjectStorage.begin(); itor != mObjectStorage.end(); ++itor)
			itor->second.applyModel();
	}

	// 업데이트
	void update(float& dt)
	{
		for (auto itor = mObjectStorage.begin(); itor != mObjectStorage.end(); ++itor)
			itor->second.update(dt);
	}

	// 플레이어 지정
	void setPlayer(string _playerName)
	{
		mPlayerName = _playerName;
	}

	// 플레이어 애니 변경
	void playrSetAni(string _aniName)
	{
		mObjectStorage[mPlayerName].setAni(_aniName);
	}

	// 플레이어 이동
	void playerMoveX(float _power)
	{
		mObjectStorage[mPlayerName].moveModelX(_power);
	}

	void playerMoveY(float _power)
	{
		mObjectStorage[mPlayerName].moveModelY(_power);
	}

	void playerMoveZ(float _power)
	{
		mObjectStorage[mPlayerName].moveModelZ(_power);
	}

private:
#ifdef DEBUG_MODE
	// 기본 매쉬 초기화
	void _initDefaultMesh()
	{
		// 좌표계 매쉬 초기화
		_initAxis();

		// 그리드 초기화
		_initGrid();

		// 땅 초기화
		_initGround();
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

	// 땅 초기화
	void _initGround()
	{
		Plane plane(Vector3::UNIT_Y, 0);
		MeshManager::getSingleton().createPlane(
			"Ground",
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			plane,
			500, 500,
			1, 1,
			true, 1, 5, 5,
			Vector3::NEGATIVE_UNIT_Z
			);

		Entity* ground = mCoreStorage->mSceneMgr->createEntity("GroundPlane", "Ground");
		mCoreStorage->mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ground);
		ground->setMaterialName("KPU_LOGO");
		//mGround->setCastShadows(false);
	}
#endif
};

