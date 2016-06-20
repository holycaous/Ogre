#pragma once
class PostEffect : public cSingleton<PostEffect>
{
	// 코어 저장창고
	CoreStorage* mCoreStorage = CoreStorage::getInstance();
	
	// 오버레이 시스템& 매니저
	Ogre::OverlaySystem   * mOverlaySystem;
	Ogre::OverlayManager  * mOverlayMgr;

	// 이미지 저장창고
	std::map<string, Overlay*> mImageStroage;

	Ogre::Overlay         * mMainOverlay;
	Ogre::Overlay         * mGameLogoOverlay;
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
#ifdef DEBUG_MODE
		// FPS 업데이트
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
	// Text 그리기
	void _setOverlay()
	{
		// 오버레이 매니저 만들기
		mOverlayMgr  = OverlayManager::getSingletonPtr();
		mTextOverlay = mOverlayMgr->create("TextOverlay");

		// 패널 만들기
		mPanel = static_cast<Ogre::OverlayContainer*>(mOverlayMgr->createOverlayElement("Panel", "container1"));
		mPanel->setDimensions(1, 1);
		mPanel->setPosition(0.0f, 0.0f);

		//// 텍스트 만들기
		//OverlayElement* textBox = mOverlayMgr->createOverlayElement("TextArea", "TextID");
		//textBox->setMetricsMode(Ogre::GMM_PIXELS);
		//textBox->setPosition(478, 312);
		//textBox->setWidth(100);
		//textBox->setHeight(20);
		//textBox->setParameter("font_name", "Font/NanumBold18");
		//textBox->setParameter("char_height", "18");
		//textBox->setColour(Ogre::ColourValue::White);
		//textBox->setCaption(L"플레이어");
		//mPanel->addChild(textBox);

		//// 텍스트 붙이기
		//mTextOverlay->add2D(mPanel);


		// 이미지 만들기
		mMainOverlay = OverlayManager::getSingleton().getByName("Overlay/MAIN_IMAGE");
		mGameLogoOverlay = OverlayManager::getSingleton().getByName("Overlay/GAME_LOGO");

		// Fill Here -----------------------------------------------
		// 이거 디버그 패널이라고 되어있는걸로 보아, 미리 준비된 패널일가능성이 높음.
		mInformationOverlay = OverlayManager::getSingleton().getByName("Overlay/Information");
		// ---------------------------------------------------------
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
		tOverlay->show();  // <--- 음.. 일단 보이기?? 수정해야함.
		//---------------------------------------------------------------------------------------//

		// 저장
		mImageStroage[_overlayName] = tOverlay;
	}

	// 텍스터 켜기
	void _onText(string _overlayName)
	{
		mImageStroage[_overlayName]->show();
	}

	// 텍스터 끄기
	void _offText(string _overlayName)
	{
		mImageStroage[_overlayName]->hide();
	}
};

