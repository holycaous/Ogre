#pragma once
class Cam : public cSingleton<Cam>
{
private:
	Vector3 mPos;
	Vector3 mlook;

	CoreStorage* mCoreStorage = CoreStorage::getInstance();

	Camera  * mCamera;
	Viewport* mViewport;

	float mSpeed;
	float mRotSpeed;
	float mDt = 0.0f;
public:
	void init()
	{
		mCamera = mCoreStorage->mSceneMgr->createCamera("main");

		// 카메라 초기화
		mPos.x = 0.0f;
		mPos.y = 100.0f;
		mPos.z = 500.0f;

		mlook.x = 0.0f;
		mlook.y = 100.0f;
		mlook.z = 0.0f;

		mSpeed    = 25.0f;
		mRotSpeed = 50.0f;

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
		mDt = dt;
		mCamera->setPosition(mPos);
	}

	void SetX(float _x)
	{
		mPos.x += _x * mDt;
	}

	void SetY(float _y)
	{
		mPos.y += _y * mDt;
	}

	void SetZ(float _z)
	{
		mPos.z += _z * mDt;
	}

	void RotateX(const OIS::MouseEvent &e)
	{
		mCamera->pitch(Degree((Real)-e.state.Y.rel* mDt * mRotSpeed));
	}

	void RotateY(const OIS::MouseEvent &e)
	{
		mCamera->yaw(Degree((Real)-e.state.X.rel * mDt * mRotSpeed));
	}

	void clearClass()
	{

	}


};

