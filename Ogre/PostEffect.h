#pragma once
class PostEffect : public cSingleton<PostEffect>
{
	// 코어 저장창고
	CoreStorage* mCoreStorage = CoreStorage::getInstance();
	
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

		// 패널 만들기
		mPanel = static_cast<Ogre::OverlayContainer*>(mOverlayMgr->createOverlayElement("Panel", "container1"));
		mPanel->setDimensions(1, 1);
		mPanel->setPosition(0.0f, 0.0f);

		// 텍스트 만들기
		_addText("TextOverlay", L"player", "18", 485, 312);

		// 이미지 만들기
		// 패널들 이름은 중복되지않게 임의로 지어주면, 알아서 만드는 듯?
		_addImage("MainOverlay"       , "Overlay/MAIN_IMAGE");
		_addImage("GameLogoOverlay"   , "Overlay/GAME_LOGO");
		_addImage("InformationOverlay", "Overlay/Information"); 
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

