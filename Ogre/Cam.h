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
		mPos.x = 0.0f;
		mPos.y = 1050.0f;
		mPos.z = 1050.0f;

		mlook.x = 0.0f;
		mlook.y = 100.0f;
		mlook.z = 0.0f;


		// 카메라 초기화
		mCamera->setPosition(mPos);
		mCamera->lookAt(mlook);

		mCamera->setNearClipDistance(5.0f);

		mViewport = mCoreStorage->mWindow->addViewport(mCamera);
		mViewport->setBackgroundColour(ColourValue(0.0f, 0.0f, 0.5f));
		mCamera->setAspectRatio(Real(mViewport->getActualWidth()) / Real(mViewport->getActualHeight()));

	}

	// 업데이트
	void Update(float dt)
	{
		mDeltaTime = dt;
		mCamera->setPosition(mPos);
	}

	void SetX(float _x)
	{
		mPos.x += _x * mDeltaTime;
	}

	void SetY(float _y)
	{
		mPos.y += _y * mDeltaTime;
	}

	void SetZ(float _z)
	{
		mPos.z += _z * mDeltaTime;
	}

	void clearClass()
	{

	}
};

