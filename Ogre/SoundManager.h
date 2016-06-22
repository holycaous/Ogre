#pragma once

class SoundManager : public cSingleton<SoundManager>
{
	std::map<string, MCI_OPEN_PARMS> mSoundStorage;
public:
	void init()
	{
		// ���� �߰�
		_addSound("Attack1", "Sound_Attack1.wav" );
		_addSound("Attack2", "Sound_Attack2.wav" );
		_addSound("GetItem", "Sound_Get_Item.wav");
		_addSound("End"    , "End.wav"		     );
	}

	void clearClass()
	{
		// �ݱ�
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
		// ���
		MCI_PLAY_PARMS mciPlay;
		auto dwID = mSoundStorage[_soundName].wDeviceID;
		mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
		mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);

		//MCI_NOTIFY : �⺻, MCI_DGV_PLAY_REPEAT : �ݺ�
	}

private:
	void _addSound(string _soundName, string _fileName, string _fileType = "waveaudio")
	{
		// ���� ����
		MCI_OPEN_PARMS tMciOpen;			          // MCI_OPEN_PARAMS ����ü ���� 
		tMciOpen.lpstrDeviceType  = _fileType.c_str(); // mpegvideo : mp3, waveaudio : wav, avivideo : avi
		tMciOpen.lpstrElementName = _fileName.c_str(); // �����̸�
		mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE , (DWORD)(LPVOID)&tMciOpen);

		// ����
		mSoundStorage[_soundName] = tMciOpen;
	}
};

