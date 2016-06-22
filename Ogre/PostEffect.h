#pragma once
class PostEffect : public cSingleton<PostEffect>
{
	// 코어 저장창고
	CoreStorage * mCoreStorage  = CoreStorage::getInstance();
	ModelManager* mModelManager = ModelManager::getInstance();
	
	// 오버레이 시스템& 매니저
	Ogre::OverlaySystem   * mOverlaySystem;
	Ogre::OverlayManager  * mOverlayMgr;

	// 패널
	Ogre::OverlayContainer* mPanel;

	// 이미지 저장창고
	std::map<string, Overlay*> mImageStroage;

public:
	void init()
	{
		// 오버레이 시스템 생성
		mOverlaySystem = new Ogre::OverlaySystem();
		mCoreStorage->mSceneMgr->addRenderQueueListener(mOverlaySystem);
	}

	// 오버레이 셋
	void setoverlay()
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
#ifdef DEBUG_MODE
		// FPS 업데이트
		_updateFPS();
#endif
		// HP 업데이트
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
		guiAvg  ->setCaption(avgFps   + StringConverter::toString(stats.avgFPS));
		guiCurr ->setCaption(currFps  + StringConverter::toString(stats.lastFPS));
		guiBest ->setCaption(bestFps  + StringConverter::toString(stats.bestFPS));
		guiWorst->setCaption(worstFps + StringConverter::toString(stats.worstFPS));
	}
#endif

	// HP 업데이트
	void _updateHP()
	{
		static int one, ten;

		// 플레이어 hp
		int tPlayerHP = mModelManager->getPlayerHP();

		// 1의자리
		// 기존것 지우기
		_calHpNum(one, 150);

		// 새로 계산해서 넣기
		one = tPlayerHP % 10;
		_calHpNum(one, 200);

		// 10의자리
		// 기존것 지우기
		_calHpNum(ten * 10, 150);

		// 새로 계산해서 넣기
		ten = tPlayerHP / 10;
		_calHpNum(ten * 10, 200);
	}

	// HP 계산
	void _calHpNum(int _num, int _zOder)
	{
		// 임시 버퍼
		char buf[64];
		memset(buf, '\0', sizeof(buf));
		itoa10(_num, buf);
		string hp = "HP_";
		hp += buf;
		_setZoder(hp, _zOder);
	}

	// Z 오더 set
	void _setZoder(string _overlay, int _zOder)
	{
		mImageStroage[_overlay.c_str()]->setZOrder(_zOder);
	}

	// Text 그리기
	void _setOverlay()
	{
		// 오버레이 매니저 만들기
		mOverlayMgr  = OverlayManager::getSingletonPtr();

		// 패널 만들기
		mPanel = static_cast<Ogre::OverlayContainer*>(mOverlayMgr->createOverlayElement("Panel", "container1"));
		mPanel->setDimensions(1, 1);
		mPanel->setPosition(0.0f, 0.0f);

		// 텍스트 만들기
		_addText("TextOverlay", L"player", "18", 490, 312);

		// 이미지 만들기
		// 패널들 이름은 중복되지않게 임의로 지어주면, 알아서 만드는 듯?
		_addImage("MainOverlay"       , "Overlay/MAIN_IMAGE");
		_addImage("GameLogoOverlay"   , "Overlay/GAME_LOGO");
		_addImage("PlayerHP"          , "Overlay/PLAYER_HP");

		// 각 숫자 만들기
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

	// 이미지 추가
	void _addImage(string _overlayName, string _imageNmae)
	{
		mImageStroage[_overlayName] = OverlayManager::getSingleton().getByName(_imageNmae.c_str());
	}

	// 텍스트 추가
	void _addText(string _overlayName, wstring _text, string _fontSize, float _x, float _y)
	{
		// 임시 저장공간
		Overlay* tOverlay;

		//---------------------------------------------------------------------------------------//
		// 초기화
		//---------------------------------------------------------------------------------------//
		tOverlay = mOverlayMgr->create(_overlayName.c_str());

		// TextArea 쉐이더로 만들기 
		OverlayElement* textBox = mOverlayMgr->createOverlayElement("TextArea", "TextID"); //@@@@@@@ TextID 가 문제될 수 있음!!

		// 어떤식으로 렌더링할 것인가
		textBox->setMetricsMode(Ogre::GMM_PIXELS);

		// 텍스트 박스 크기
		textBox->setWidth(100); //<-- 완전 넉넉하게 잡는듯
		textBox->setHeight(20); //<-- 완전 넉넉하게 잡는듯

		// 위치
		textBox->setPosition(_x, _y);
		textBox->setParameter("font_name", "Font/NanumBold18");
		textBox->setParameter("char_height", _fontSize.c_str());
		textBox->setColour(Ogre::ColourValue::White);

		// 입력된 텍스트
		textBox->setCaption(_text.c_str());

		// 텍스트 붙이기
		mPanel->addChild(textBox);
		tOverlay->add2D(mPanel);
		//---------------------------------------------------------------------------------------//

		// 저장
		mImageStroage[_overlayName] = tOverlay;
	}

	// 오버레이 켜기
	void _onOverlay(string _overlayName)
	{
		mImageStroage[_overlayName]->show();
	}

	// 오버레이 끄기
	void _offOverlay(string _overlayName)
	{
		mImageStroage[_overlayName]->hide();
	}
};

