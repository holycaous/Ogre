#pragma once

class SoundManager : public cSingleton<SoundManager>
{
	//System* mSystem;
	//std::map<string, Sound*> mSoundStorage; // ���� ������ŭ �ʿ�
	//std::map<string, Channel*> mChannel;    // ���ÿ� ��µ� ���� ������ŭ �ʿ�

	//bool  bPlay           = true;
	//bool  IsBGPlaying     = false;
	//bool  IsEffectPlaying = false;
	//float fVolume         = 1;
public:
	void init()
	{
		////���� �ý����� ����
		//System_Create(&mSystem);

		////	���� �ý��� �⺻ ����
		//mSystem->init(2, FMOD_INIT_NORMAL, NULL);

		//// ���� ���� �ʱ�ȭ
		//_initSoundFile();
	}

	void clearClass()
	{
		//// ���� ����
		//for (auto itor = mSoundStorage.begin(); itor != mSoundStorage.end(); ++itor)
		//	itor->second->release();

		//// �ý��� ����
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

