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
		// �������� �ý��� ����
		mOverlaySystem = new Ogre::OverlaySystem();
		mCoreStorage->mSceneMgr->addRenderQueueListener(mOverlaySystem);
	}

	// �������� ��
	void setOverly()
	{
		// �������� ����
		_setOverlay();
	}

	void clearClass()
	{
	}

	// ������Ʈ
	void update()
	{
		// FPS ������Ʈ
		_updateFPS();

	}

	
private:
	// FPS ������Ʈ
	void _updateFPS()
	{
		static Ogre::DisplayString currFps  = L"���� FPS: ";
		static Ogre::DisplayString avgFps   = L"��� FPS: ";
		static Ogre::DisplayString bestFps  = L"�ְ� FPS: ";
		static Ogre::DisplayString worstFps = L"���� FPS: ";
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

	// Text �׸���
	void _setOverlay()
	{
		// �������� �Ŵ��� �����
		mOverlayMgr = OverlayManager::getSingletonPtr();
		mTextOverlay = mOverlayMgr->create("TextOverlay");

		// �г� �����
		mPanel = static_cast<Ogre::OverlayContainer*>(mOverlayMgr->createOverlayElement("Panel", "container1"));
		mPanel->setDimensions(1, 1);
		mPanel->setPosition(0.0f, 0.0f);

		// �ؽ�Ʈ �����
		OverlayElement* textBox = mOverlayMgr->createOverlayElement("TextArea", "TextID");
		textBox->setMetricsMode(Ogre::GMM_PIXELS);
		textBox->setPosition(10, 10);
		textBox->setWidth(100);
		textBox->setHeight(20);
		textBox->setParameter("font_name", "Font/NanumBold18");
		textBox->setParameter("char_height", "40");
		textBox->setColour(Ogre::ColourValue::White);
		textBox->setCaption(L"�׽�Ʈ");
		mPanel->addChild(textBox);

		mTextOverlay->add2D(mPanel);
		mTextOverlay->show();

		// �̹��� �����
		mLogoOverlay = OverlayManager::getSingleton().getByName("Overlay/KPU_LOGO");
		mLogoOverlay->show();

		// Fill Here -----------------------------------------------
		// �̰� ����� �г��̶�� �Ǿ��ִ°ɷ� ����, �̸� �غ�� �г��ϰ��ɼ��� ����.
		mInformationOverlay = OverlayManager::getSingleton().getByName("Overlay/Information");
		mInformationOverlay->show();
		// ---------------------------------------------------------

	}
};

