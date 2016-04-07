#pragma once
class ModelManager : public cSingleton<ModelManager>
{
	CoreStorage* mCoreStorage = CoreStorage::getInstance();

	// 엔티티 & 씬노드
	std::vector<Entity*>    mEntity;
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
		// 기본 초기화
		_initDefault();
#endif
	}

	void clearClass()
	{

	}

	// 모델 클리어
	void clearModel()
	{
		mEntity.clear();
		mSceneNode.clear();
	}

	// 모델 추가
	void addModel(char* _objName, char* _meshName, float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
	{
		// 엔티티 & 노드 추가
		mEntity   .push_back(mCoreStorage->mSceneMgr->createEntity(_objName, _meshName));
		mSceneNode.push_back(mCoreStorage->mSceneMgr->getRootSceneNode()->createChildSceneNode(_objName, Vector3(_x, _y, _z)));
	}

	// 무작정 있는거 다 그리기
	void DrawAll()
	{
#ifdef DEBUG_MODE
		// 그리드 표시
		gridPlaneNode->attachObject(gridPlane);
#endif

		// 모든 오브젝트 붙이기
		for (unsigned int i = 0; i < mSceneNode.size(); ++i)
			mSceneNode[i]->attachObject(mEntity[i]);
	}

private:
#ifdef DEBUG_MODE
	// 기본 초기화
	void _initDefault()
	{
		// 좌표계 매쉬 초기화
		mAxis     = mCoreStorage->mSceneMgr->createEntity("Axis", "axes.mesh");
		mAxisNode = mCoreStorage->mSceneMgr->getRootSceneNode()->createChildSceneNode("Axis", Vector3(0.0f, 0.0f, 0.0f));
		mCoreStorage->mRoot->getSceneManager("main")->getSceneNode("Axis")->setScale(5, 5, 5);

		// 엔진 그리드 초기화
		_initGrid();
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

