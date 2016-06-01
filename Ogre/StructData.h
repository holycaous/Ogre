#pragma once

// ��������
enum
{
	e_MainState = 0,
	e_PlayState = 1
};

// ��ƼƼ ������
class Model
{
public:
	// �� ����
	Entity   * mObject;

	// ���� ��Ʈ����
	SceneNode* mWdMtx;

	// ���� ����
	Vector3 mLookDir;

	// �ִϸ��̼� ��������
	std::map<string, AnimationState*> mAniStorage;

	// ���� ����Ǵ� ���ϸ��̼�
	AnimationState* mSelctAni;

	// ��Ÿ Ÿ��
	float mDeltaTime;

public:
	~Model()
	{
		_clearClass();
	}

	// �� �ʱ�ȭ
	void initModel(string _objName, string _meshDataName, float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
	{
		mLookDir = Vector3(0.0f, 0.0f, -1.0f);
		mObject  = CoreStorage::getInstance()->mSceneMgr->createEntity(_objName.c_str(), _meshDataName.c_str());
		mWdMtx   = CoreStorage::getInstance()->mSceneMgr->getRootSceneNode()->createChildSceneNode(_objName.c_str(), Vector3(_x, _y, _z));
	}

	// �ִϸ��̼� �ʱ�ȭ
	void initAni(string _objName, string _aniName)
	{
		// �ִϸ��̼� �߰�
		AnimationState* tNewAni = CoreStorage::getInstance()->mRoot->getSceneManager("main")->getEntity(_objName.c_str())->getAnimationState(_aniName.c_str());

		// �ִϸ��̼� ���� (�ִϸ��̼� �̸����� ã�ƾ���)
		mAniStorage[_aniName] = tNewAni;
	}

	void applyModel()
	{
		// �Էµ� �� ���̱�
		mWdMtx->attachObject(mObject);

		// �ִϸ��̼� �ѱ�
		_initAni("Idle");

		// �׸����ѱ�
		_setShadow();
	}
	
	// ������Ʈ
	void update(float& dt)
	{
		// ��Ÿ Ÿ��
		mDeltaTime = dt;

		// �ִϸ��̼� ������Ʈ
		_aniUpdate(dt);
	}

	// �� �̵���Ű��
	void moveModelX(float& _power)
	{
		// ����
		float tDir = _power < 0.0f ? 1.0f : -1.0f;
		mLookDir = Vector3(tDir, 0.0f, 0.0f);
		mWdMtx->setDirection(mLookDir, Node::TS_WORLD);

		// �̵�
		mWdMtx->translate(_power * mDeltaTime, 0.0f, 0.0f);
	}

	void moveModelY(float& _power)
	{
		// ����
		float tDir = _power < 0.0f ? 1.0f : -1.0f;
		mLookDir = Vector3(0.0f, tDir, 0.0f);
		mWdMtx->setDirection(mLookDir, Node::TS_WORLD);

		// �̵�
		mWdMtx->translate(0.0f, _power * mDeltaTime, 0.0f);
	}

	void moveModelZ(float& _power)
	{
		// ����
		float tDir = _power < 0.0f ? 1.0f : -1.0f;
		mLookDir = Vector3(0.0f, 0.0f, tDir);
		mWdMtx->setDirection(mLookDir, Node::TS_WORLD);

		// �̵�
		mWdMtx->translate(0.0f, 0.0f, _power * mDeltaTime);
	}

	// �ִϸ��̼� ����
	void setAni(string _aniName)
	{
		// �ִϸ��̼��� �ִٸ�,
		if (mAniStorage.size() != 0)
		{
			// ���� �ִ� ����
			mSelctAni->setLoop(false);
			mSelctAni->setEnabled(false);

			// �ִϸ��̼� ����
			mSelctAni = mAniStorage[_aniName];

			// ���ο� �ִϸ��̼� ����
			mSelctAni->setLoop(true);
			mSelctAni->setEnabled(true);
		}
	}

private:
	// Ŭ���� ����
	void _clearClass()
	{
		// �ִϸ��̼� â�� ����
		mAniStorage.clear();
	}

	// �׸��� �ѱ�
	void _setShadow()
	{
		mObject->setCastShadows(true);
	}

	// �׸��� ����
	void _resetShadow()
	{
		mObject->setCastShadows(false);
	}

	// �ʱ�ȭ ����
	void _initAni(string _aniName)
	{
		// �ִϸ��̼��� �ִٸ�,
		if (mAniStorage.size() != 0)
		{
			// �ִϸ��̼� ����
			mSelctAni = mAniStorage[_aniName];

			// ���ο� �ִϸ��̼� ����
			mSelctAni->setLoop(true);
			mSelctAni->setEnabled(true);
		}
	}

	// �ִϸ��̼� ������Ʈ
	void _aniUpdate(float& dt)
	{
		// �ִϸ��̼��� �ִٸ�,
		if (mAniStorage.size() != 0)
			mSelctAni->addTime(dt);
	}
};