#pragma once
class PostEffect : public cSingleton<PostEffect>
{
	CoreStorage* mCoreStorage = CoreStorage::getInstance();

	Ogre::OverlaySystem   * mOverlaySystem;
	Ogre::OverlayManager  * mOverlayMgr;
	Ogre::Overlay         * mLogoOverlay;
	Ogre::Overlay		  * mTextOverlay;
	Ogre::Overlay		  * mInformationOverlay;
	Ogre::OverlayContainer* mPanel;
public:
	void init()
	{
		// 오버레이 시스템 생성
		mOverlaySystem = new Ogre::OverlaySystem();
		mCoreStorage->mSceneMgr->addRenderQueueListener(mOverlaySystem);
	}

	// 오버레이 셋
	void setOverly()
	{
		// 오버레이 셋팅
		_setOverlay();
	}

	void clearClass()
	{
	}

	// 업데이트
	void update()
	{
		// FPS 업데이트
		_updateFPS();

	}

	
private:
	// FPS 업데이트
	void _updateFPS()
	{
		static Ogre::DisplayString currFps  = L"현재 FPS: ";
		static Ogre::DisplayString avgFps   = L"평균 FPS: ";
		static Ogre::DisplayString bestFps  = L"최고 FPS: ";
		static Ogre::DisplayString worstFps = L"최저 FPS: ";
		OverlayElement* guiAvg   = OverlayManager::getSingleton().getOverlayElement("AverageFps");
		OverlayElement* guiCurr  = OverlayManager::getSingleton().getOverlayElement("CurrFps");
		OverlayElement* guiBest  = OverlayManager::getSingleton().getOverlayElement("BestFps");
		OverlayElement* guiWorst = OverlayManager::getSingleton().getOverlayElement("WorstFps");

		const RenderTarget::FrameStats& stats =	mCoreStorage->mRoot->getAutoCreatedWindow()->getStatistics();
		guiAvg->setCaption  (avgFps   + StringConverter::toString(stats.avgFPS));
		guiCurr->setCaption (currFps  + StringConverter::toString(stats.lastFPS));
		guiBest->setCaption (bestFps  + StringConverter::toString(stats.bestFPS));
		guiWorst->setCaption(worstFps + StringConverter::toString(stats.worstFPS));

	}

	// Text 그리기
	void _setOverlay()
	{
		// 오버레이 매니저 만들기
		mOverlayMgr = OverlayManager::getSingletonPtr();
		mTextOverlay = mOverlayMgr->create("TextOverlay");

		// 패널 만들기
		mPanel = static_cast<Ogre::OverlayContainer*>(mOverlayMgr->createOverlayElement("Panel", "container1"));
		mPanel->setDimensions(1, 1);
		mPanel->setPosition(0.0f, 0.0f);

		// 텍스트 만들기
		OverlayElement* textBox = mOverlayMgr->createOverlayElement("TextArea", "TextID");
		textBox->setMetricsMode(Ogre::GMM_PIXELS);
		textBox->setPosition(10, 10);
		textBox->setWidth(100);
		textBox->setHeight(20);
		textBox->setParameter("font_name", "Font/NanumBold18");
		textBox->setParameter("char_height", "40");
		textBox->setColour(Ogre::ColourValue::White);
		textBox->setCaption(L"테스트");
		mPanel->addChild(textBox);

		mTextOverlay->add2D(mPanel);
		mTextOverlay->show();

		// 이미지 만들기
		mLogoOverlay = OverlayManager::getSingleton().getByName("Overlay/KPU_LOGO");
		mLogoOverlay->show();

		// Fill Here -----------------------------------------------
		// 이거 디버그 패널이라고 되어있는걸로 보아, 미리 준비된 패널일가능성이 높음.
		mInformationOverlay = OverlayManager::getSingleton().getByName("Overlay/Information");
		mInformationOverlay->show();
		// ---------------------------------------------------------

	}
};

