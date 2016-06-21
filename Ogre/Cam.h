#pragma once
class Cam : public cSingleton<Cam>
{
private:
	Vector3 mPos;
	Vector3 mlook;

	CoreStorage* mCoreStorage = CoreStorage::getInstance();

	Camera  * mCamera;
	Viewport* mViewport;

	float mDeltaTime = 0.0f;
public:
	void init()
	{
		mCamera = mCoreStorage->mSceneMgr->createCamera("main");

		// 카메라 초기화
		initValue();

		// 카메라 초기화
		mCamera->setPosition(mPos);
		mCamera->lookAt(mlook);

		mCamera->setNearClipDistance(5.0f);

		mViewport = mCoreStorage->mWindow->addViewport(mCamera);
		mViewport->setBackgroundColour(ColourValue(0.0f, 0.0f, 0.5f));
		mCamera->setAspectRatio(Real(mViewport->getActualWidth()) / Real(mViewport->getActualHeight()));

	}
	
	void initValue()
	{
		// 카메라 초기화
		mPos.x = 0.0f;
		mPos.y = 1050.0f;
		mPos.z = 1050.0f;

		mlook.x = 0.0f;
		mlook.y = 100.0f;
		mlook.z = 0.0f;
	}

	// 업데이트
	void Update(float dt)
	{
		mDeltaTime = dt;
		mCamera->setPosition(mPos);
	}

	void SetX(float _x)
	{
		if (mPos.x > -MAP_SIZE && mPos.x < MAP_SIZE)
			mPos.x += _x * mDeltaTime;
		else
			initValue();
	}

	void SetY(float _y)
	{
		mPos.y += _y * mDeltaTime;

		if (mPos.y > -MAP_SIZE && mPos.y < MAP_SIZE)
			mPos.y += _y * mDeltaTime;
		else
			initValue();
	}

	void SetZ(float _z)
	{
		if (mPos.z > -MAP_SIZE && mPos.z < MAP_SIZE)
			mPos.z += _z * mDeltaTime;
		else
			initValue();
	}

	void clearClass()
	{

	}
};

