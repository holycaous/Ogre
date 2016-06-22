#pragma once
class PostEffect : public cSingleton<PostEffect>
{
	// �ھ� ����â��
	CoreStorage * mCoreStorage  = CoreStorage::getInstance();
	ModelManager* mModelManager = ModelManager::getInstance();
	
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
		// HP ������Ʈ
		_updateHP();
	}

	void setPlayState()
	{
		mImageStroage["GameLogoOverlay"]   ->show();
#ifdef DEBUG_MODE
		mImageStroage["InformationOverlay"]->show();
#endif
		mImageStroage["TextOverlay"]	   ->show();
		mImageStroage["PlayerHP"]          ->show();

		mImageStroage["HP_0"]->show();
		mImageStroage["HP_1"]->show();
		mImageStroage["HP_2"]->show();
		mImageStroage["HP_3"]->show();
		mImageStroage["HP_4"]->show();
		mImageStroage["HP_5"]->show();
		mImageStroage["HP_6"]->show();
		mImageStroage["HP_7"]->show();
		mImageStroage["HP_8"]->show();
		mImageStroage["HP_9"]->show();
		mImageStroage["HP_00"]->show();
		mImageStroage["HP_10"]->show();
		mImageStroage["HP_20"]->show();
		mImageStroage["HP_30"]->show();
		mImageStroage["HP_40"]->show();
		mImageStroage["HP_50"]->show();
		mImageStroage["HP_60"]->show();
		mImageStroage["HP_70"]->show();
		mImageStroage["HP_80"]->show();
		mImageStroage["HP_90"]->show();

		mImageStroage["MainOverlay"]       ->hide();
	}

	void setMainState()
	{
		mImageStroage["GameLogoOverlay"]   ->hide();
#ifdef DEBUG_MODE
		mImageStroage["InformationOverlay"]->hide();
#endif
		mImageStroage["TextOverlay"]       ->hide();
		mImageStroage["PlayerHP"]          ->hide();

		mImageStroage["HP_0"]->hide();
		mImageStroage["HP_1"]->hide();
		mImageStroage["HP_2"]->hide();
		mImageStroage["HP_3"]->hide();
		mImageStroage["HP_4"]->hide();
		mImageStroage["HP_5"]->hide();
		mImageStroage["HP_6"]->hide();
		mImageStroage["HP_7"]->hide();
		mImageStroage["HP_8"]->hide();
		mImageStroage["HP_9"]->hide();
		mImageStroage["HP_00"]->hide();
		mImageStroage["HP_10"]->hide();
		mImageStroage["HP_20"]->hide();
		mImageStroage["HP_30"]->hide();
		mImageStroage["HP_40"]->hide();
		mImageStroage["HP_50"]->hide();
		mImageStroage["HP_60"]->hide();
		mImageStroage["HP_70"]->hide();
		mImageStroage["HP_80"]->hide();
		mImageStroage["HP_90"]->hide();

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

	// HP ������Ʈ
	void _updateHP()
	{
		static int one, ten;

		// �÷��̾� hp
		int tPlayerHP = mModelManager->getPlayerHP();

		// 1���ڸ�
		// ������ �����
		_calHpNum(one, 150);

		// ���� ����ؼ� �ֱ�
		one = tPlayerHP % 10;
		_calHpNum(one, 200);

		// 10���ڸ�
		// ������ �����
		_calHpNum(ten * 10, 150);

		// ���� ����ؼ� �ֱ�
		ten = tPlayerHP / 10;
		_calHpNum(ten * 10, 200);
	}

	// HP ���
	void _calHpNum(int _num, int _zOder)
	{
		// �ӽ� ����
		char buf[64];
		memset(buf, '\0', sizeof(buf));
		itoa10(_num, buf);
		string hp = "HP_";
		hp += buf;
		_setZoder(hp, _zOder);
	}

	// Z ���� set
	void _setZoder(string _overlay, int _zOder)
	{
		mImageStroage[_overlay.c_str()]->setZOrder(_zOder);
	}

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
		_addText("TextOverlay", L"player", "18", 490, 312);

		// �̹��� �����
		// �гε� �̸��� �ߺ������ʰ� ���Ƿ� �����ָ�, �˾Ƽ� ����� ��?
		_addImage("MainOverlay"       , "Overlay/MAIN_IMAGE");
		_addImage("GameLogoOverlay"   , "Overlay/GAME_LOGO");
		_addImage("PlayerHP"          , "Overlay/PLAYER_HP");

		// �� ���� �����
		_addImage("HP_0", "Overlay/HP_0");
		_addImage("HP_1", "Overlay/HP_1");
		_addImage("HP_2", "Overlay/HP_2");
		_addImage("HP_3", "Overlay/HP_3");
		_addImage("HP_4", "Overlay/HP_4");
		_addImage("HP_5", "Overlay/HP_5");
		_addImage("HP_6", "Overlay/HP_6");
		_addImage("HP_7", "Overlay/HP_7");
		_addImage("HP_8", "Overlay/HP_8");
		_addImage("HP_9", "Overlay/HP_9");
		_addImage("HP_00", "Overlay/HP_00");
		_addImage("HP_10", "Overlay/HP_10");
		_addImage("HP_20", "Overlay/HP_20");
		_addImage("HP_30", "Overlay/HP_30");
		_addImage("HP_40", "Overlay/HP_40");
		_addImage("HP_50", "Overlay/HP_50");
		_addImage("HP_60", "Overlay/HP_60");
		_addImage("HP_70", "Overlay/HP_70");
		_addImage("HP_80", "Overlay/HP_80");
		_addImage("HP_90", "Overlay/HP_90");

#ifdef DEBUG_MODE
		_addImage("InformationOverlay", "Overlay/Information"); 
#endif
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

