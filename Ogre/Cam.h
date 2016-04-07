#pragma once
class Cam : public cSingleton<Cam>
{
	CoreStorage* mCoreStorage = CoreStorage::getInstance();

	Camera  * mCamera;
	Viewport* mViewport;
public:
	void init()
	{
		mCamera = mCoreStorage->mSceneMgr->createCamera("main");

		// 카메라 초기화
		mCamera->setPosition(0.0f, 100.0f, 500.0f);
		mCamera->lookAt(0.0f, 100.0f, 0.0f);

		mCamera->setNearClipDistance(5.0f);

		mViewport = mCoreStorage->mWindow->addViewport(mCamera);
		mViewport->setBackgroundColour(ColourValue(0.0f, 0.0f, 0.5f));
		mCamera->setAspectRatio(Real(mViewport->getActualWidth()) / Real(mViewport->getActualHeight()));
	}

	void clearClass()
	{

	}


};

