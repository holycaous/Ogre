#pragma once

class SoundManager : public cSingleton<SoundManager>
{
	//System* mSystem;
	//std::map<string, Sound*> mSoundStorage; // 사운드 갯수만큼 필요
	//std::map<string, Channel*> mChannel;    // 동시에 출력될 사운드 갯수만큼 필요

	//bool  bPlay           = true;
	//bool  IsBGPlaying     = false;
	//bool  IsEffectPlaying = false;
	//float fVolume         = 1;
public:
	void init()
	{
		////사운드 시스템을 생성
		//System_Create(&mSystem);

		////	사운드 시스템 기본 세팅
		//mSystem->init(2, FMOD_INIT_NORMAL, NULL);

		//// 사운드 파일 초기화
		//_initSoundFile();
	}

	void clearClass()
	{
		//// 사운드 해제
		//for (auto itor = mSoundStorage.begin(); itor != mSoundStorage.end(); ++itor)
		//	itor->second->release();

		//// 시스템 해제
		//mSystem->release();
		//mSystem->close();
	}

	void update()
	{

	}
private:
	void _initSoundFile()
	{



	}

	/*void _addSound(string _soundKey, string _soundLocation)
	{
		Sound* tSound;
		mSystem->createSound(_soundLocation.c_str(), FMOD_HARDWARE | FMOD_LOOP_OFF, NULL, &tSound);
		mSoundStorage[_soundKey] = tSound;
	}

	void addBGM(string _soundKey, string _soundLocation)
	{
		Sound* tSound;
		mSystem->createSound(_soundLocation.c_str(), FMOD_HARDWARE, NULL, &tSound);
		mSoundStorage[_soundKey] = tSound;
	}*/
};

