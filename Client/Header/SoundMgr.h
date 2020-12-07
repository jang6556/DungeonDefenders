#pragma once
_BEGIN(Client)
class CSoundMgr
{
private:
	static CSoundMgr* pSceneInstance;
public:
	enum CHANNEL_ID 
	{ BGM, 
	  BULLET,
	  TOWER0,
	  TOWER1,
	  TOWER2,
	  LEVELUP,
	  BLOOD,
	  MISSILE_TOWER,
	  LIGHTNING_TOWER,
	  STRIKE_TOWER,
	  STRIKE_TOWER_CHARGE,
	  BOMB,
	  BUILD_ING,
	  BUILD_COMPLETE,
	  CLICK,
	  END };

	static CSoundMgr* GetSceneInst()
	{
		if (pSceneInstance == nullptr)
		{
			pSceneInstance = new CSoundMgr;
		}
		return pSceneInstance;
	}

	static void DestroyInst()
	{
		if (pSceneInstance != nullptr)
		{
			delete pSceneInstance;
			pSceneInstance = nullptr;
		}
	}

public:
	CSoundMgr();
	~CSoundMgr();

public:
	void Initialize();
	void Update();
	void PlaySound(const string& strSoundKey, CHANNEL_ID eID);
	void PlayBGM(const string& strSoundKey);
	void StopSound(CHANNEL_ID eID);
	void StopAll();
	FMOD_BOOL IsPlayingCheck(CHANNEL_ID eID);

private:
	void LoadSoundFile();
	void Release();

private:
	FMOD_SYSTEM*				m_pSystem;	// 사운드 장치를 제어하는 시스템 구조체.
	FMOD_CHANNEL*				m_pChannel[END]; // 실제 사운드를 재생할 채널.
	map<string, FMOD_SOUND*>	m_mapSound;
	FMOD_BOOL					IsPlaying;
};
_END
