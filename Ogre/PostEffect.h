#pragma once
class PostEffect : public cSingleton<PostEffect>
{
	// �ھ� ����â��
	CoreStorage* mCoreStorage = CoreStorage::getInstance();
	
	// �������� �ý���& �Ŵ���
	Ogre::OverlaySystem   * mOverlaySystem;
	Ogre::OverlayManager  * mOverlayMgr;

	// �г�
	Ogre::OverlayContainer* mPanel;

	// �̹��� ����â��
	std::map<string, Overlay*> mImageStroage;

public:
	void init()
	{
		// �������� �ý��� ����
		mOverlaySystem = new Ogre::OverlaySystem();
		mCoreStorage->mSceneMgr->addRenderQueueListener(mOverlaySystem);
	}

	// �������� ��
	void setoverlay()
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
		mImageStroage["GameLogoOverlay"]   ->show();
		mImageStroage["InformationOverlay"]->show();
		mImageStroage["TextOverlay"]	   ->show();

		mImageStroage["MainOverlay"]->hide();
	}

	void setMainState()
	{
		mImageStroage["GameLogoOverlay"]   ->hide();
		mImageStroage["InformationOverlay"]->hide();
		mImageStroage["TextOverlay"]       ->hide();

		mImageStroage["MainOverlay"]->show();
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

		// �г� �����
		mPanel = static_cast<Ogre::OverlayContainer*>(mOverlayMgr->createOverlayElement("Panel", "container1"));
		mPanel->setDimensions(1, 1);
		mPanel->setPosition(0.0f, 0.0f);

		// �ؽ�Ʈ �����
		_addText("TextOverlay", L"player", "18", 485, 312);

		// �̹��� �����
		// �гε� �̸��� �ߺ������ʰ� ���Ƿ� �����ָ�, �˾Ƽ� ����� ��?
		_addImage("MainOverlay"       , "Overlay/MAIN_IMAGE");
		_addImage("GameLogoOverlay"   , "Overlay/GAME_LOGO");
		_addImage("InformationOverlay", "Overlay/Information"); 
	}

	// �̹��� �߰�
	void _addImage(string _overlayName, string _imageNmae)
	{
		mImageStroage[_overlayName] = OverlayManager::getSingleton().getByName(_imageNmae.c_str());
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
		//---------------------------------------------------------------------------------------//

		// ����
		mImageStroage[_overlayName] = tOverlay;
	}

	// �������� �ѱ�
	void _onOverlay(string _overlayName)
	{
		mImageStroage[_overlayName]->show();
	}

	// �������� ����
	void _offOverlay(string _overlayName)
	{
		mImageStroage[_overlayName]->hide();
	}
};

