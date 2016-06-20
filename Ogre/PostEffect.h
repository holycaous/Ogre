#pragma once
class PostEffect : public cSingleton<PostEffect>
{
	// �ھ� ����â��
	CoreStorage* mCoreStorage = CoreStorage::getInstance();
	
	// �������� �ý���& �Ŵ���
	Ogre::OverlaySystem   * mOverlaySystem;
	Ogre::OverlayManager  * mOverlayMgr;

	// �̹��� ����â��
	std::map<string, Overlay*> mImageStroage;

	Ogre::Overlay         * mMainOverlay;
	Ogre::Overlay         * mGameLogoOverlay;
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
#ifdef DEBUG_MODE
		// FPS ������Ʈ
		_updateFPS();
#endif
	}

	void setPlayState()
	{
		mGameLogoOverlay->show();
		mInformationOverlay->show();
		//mTextOverlay->show();

		mMainOverlay->hide();
	}

	void setMainState()
	{
		mGameLogoOverlay->hide();
		mInformationOverlay->hide();
		//mTextOverlay->hide();

		mMainOverlay->show();
	}


	
private:
#ifdef DEBUG_MODE
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
		guiAvg  ->setCaption(avgFps   + StringConverter::toString(stats.avgFPS));
		guiCurr ->setCaption(currFps  + StringConverter::toString(stats.lastFPS));
		guiBest ->setCaption(bestFps  + StringConverter::toString(stats.bestFPS));
		guiWorst->setCaption(worstFps + StringConverter::toString(stats.worstFPS));
	}
#endif
	// Text �׸���
	void _setOverlay()
	{
		// �������� �Ŵ��� �����
		mOverlayMgr  = OverlayManager::getSingletonPtr();
		mTextOverlay = mOverlayMgr->create("TextOverlay");

		// �г� �����
		mPanel = static_cast<Ogre::OverlayContainer*>(mOverlayMgr->createOverlayElement("Panel", "container1"));
		mPanel->setDimensions(1, 1);
		mPanel->setPosition(0.0f, 0.0f);

		//// �ؽ�Ʈ �����
		//OverlayElement* textBox = mOverlayMgr->createOverlayElement("TextArea", "TextID");
		//textBox->setMetricsMode(Ogre::GMM_PIXELS);
		//textBox->setPosition(478, 312);
		//textBox->setWidth(100);
		//textBox->setHeight(20);
		//textBox->setParameter("font_name", "Font/NanumBold18");
		//textBox->setParameter("char_height", "18");
		//textBox->setColour(Ogre::ColourValue::White);
		//textBox->setCaption(L"�÷��̾�");
		//mPanel->addChild(textBox);

		//// �ؽ�Ʈ ���̱�
		//mTextOverlay->add2D(mPanel);


		// �̹��� �����
		mMainOverlay = OverlayManager::getSingleton().getByName("Overlay/MAIN_IMAGE");
		mGameLogoOverlay = OverlayManager::getSingleton().getByName("Overlay/GAME_LOGO");

		// Fill Here -----------------------------------------------
		// �̰� ����� �г��̶�� �Ǿ��ִ°ɷ� ����, �̸� �غ�� �г��ϰ��ɼ��� ����.
		mInformationOverlay = OverlayManager::getSingleton().getByName("Overlay/Information");
		// ---------------------------------------------------------
	}

	// �ؽ�Ʈ �߰�
	void _addText(string _overlayName, wstring _text, string _fontSize, float _x, float _y)
	{
		// �ӽ� �������
		Overlay* tOverlay;

		//---------------------------------------------------------------------------------------//
		// �ʱ�ȭ
		//---------------------------------------------------------------------------------------//
		tOverlay = mOverlayMgr->create(_overlayName.c_str());

		// TextArea ���̴��� ����� 
		OverlayElement* textBox = mOverlayMgr->createOverlayElement("TextArea", "TextID"); //@@@@@@@ TextID �� ������ �� ����!!

		// ������� �������� ���ΰ�
		textBox->setMetricsMode(Ogre::GMM_PIXELS);

		// �ؽ�Ʈ �ڽ� ũ��
		textBox->setWidth(100); //<-- ���� �˳��ϰ� ��µ�
		textBox->setHeight(20); //<-- ���� �˳��ϰ� ��µ�

		// ��ġ
		textBox->setPosition(_x, _y);
		textBox->setParameter("font_name", "Font/NanumBold18");
		textBox->setParameter("char_height", _fontSize.c_str());
		textBox->setColour(Ogre::ColourValue::White);

		// �Էµ� �ؽ�Ʈ
		textBox->setCaption(_text.c_str());

		// �ؽ�Ʈ ���̱�
		mPanel->addChild(textBox);
		tOverlay->add2D(mPanel);
		tOverlay->show();  // <--- ��.. �ϴ� ���̱�?? �����ؾ���.
		//---------------------------------------------------------------------------------------//

		// ����
		mImageStroage[_overlayName] = tOverlay;
	}

	// �ؽ��� �ѱ�
	void _onText(string _overlayName)
	{
		mImageStroage[_overlayName]->show();
	}

	// �ؽ��� ����
	void _offText(string _overlayName)
	{
		mImageStroage[_overlayName]->hide();
	}
};

