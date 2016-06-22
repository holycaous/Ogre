#pragma once

class SoundManager : public cSingleton<SoundManager>
{
	std::map<string, MCI_OPEN_PARMS> mSoundStorage;
public:
	void init()
	{
		// 사운드 추가
		_addSound("Attack1", "Sound_Attack1.wav" );
		_addSound("Attack2", "Sound_Attack2.wav" );
		_addSound("GetItem", "Sound_Get_Item.wav");
		_addSound("End"    , "End.wav"		     );
	}

	void clearClass()
	{
		// 닫기
		for (auto itor = mSoundStorage.begin(); itor != mSoundStorage.end(); ++itor)
		{
			auto dwID = itor->second.wDeviceID;
			mciSendCommand(dwID, MCI_CLOSE, 0, NULL);
		}


		PlaySound(NULL, NULL, NULL);
		mSoundStorage.clear();
	}

	void update()
	{

	}
	
	void setPlayStateBGM()
	{
		sndPlaySoundA("Sound_BGM_Play.wav", SND_ASYNC | SND_NODEFAULT | SND_LOOP);
	}

	void setMainStateBGM()
	{
		sndPlaySoundA("Sound_BGM_Main.wav",SND_ASYNC | SND_NODEFAULT | SND_LOOP);
	}

	void playSound(string _soundName)
	{
		// 재생
		MCI_PLAY_PARMS mciPlay;
		auto dwID = mSoundStorage[_soundName].wDeviceID;
		mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
		mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);

		//MCI_NOTIFY : 기본, MCI_DGV_PLAY_REPEAT : 반복
	}

private:
	void _addSound(string _soundName, string _fileName, string _fileType = "waveaudio")
	{
		// 파일 열기
		MCI_OPEN_PARMS tMciOpen;			          // MCI_OPEN_PARAMS 구조체 변수 
		tMciOpen.lpstrDeviceType  = _fileType.c_str(); // mpegvideo : mp3, waveaudio : wav, avivideo : avi
		tMciOpen.lpstrElementName = _fileName.c_str(); // 파일이름
		mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE , (DWORD)(LPVOID)&tMciOpen);

		// 저장
		mSoundStorage[_soundName] = tMciOpen;
	}
};

