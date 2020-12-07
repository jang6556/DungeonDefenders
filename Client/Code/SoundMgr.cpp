#include "stdafx.h"
#include "SoundMgr.h"


_USING(Client)

CSoundMgr* CSoundMgr::pSceneInstance = nullptr;

CSoundMgr::CSoundMgr()
{
}


CSoundMgr::~CSoundMgr()
{
	Release();
}

void CSoundMgr::Initialize()
{
	FMOD_System_Create(&m_pSystem);
	FMOD_System_Init(m_pSystem, END, FMOD_INIT_NORMAL, nullptr);

	LoadSoundFile();
}

void CSoundMgr::Update()
{
	FMOD_System_Update(m_pSystem);
}

void CSoundMgr::PlaySound(const string & strSoundKey, CHANNEL_ID eID)
{
	auto iter_find = m_mapSound.find(strSoundKey);

	if (m_mapSound.end() == iter_find)
		return;

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE,
		iter_find->second, FALSE, &(m_pChannel[eID]));

	
}

void CSoundMgr::PlayBGM(const string & strSoundKey)
{
	auto iter_find = m_mapSound.find(strSoundKey);

	if (m_mapSound.end() == iter_find)
		return;
	
	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE,
		iter_find->second, FALSE, &(m_pChannel[BGM]));

	FMOD_Channel_SetMode(m_pChannel[BGM], FMOD_LOOP_NORMAL);
	FMOD_Channel_SetVolume(m_pChannel[BGM], 0.5f);
}

void CSoundMgr::StopSound(CHANNEL_ID eID)
{
	FMOD_Channel_Stop(m_pChannel[eID]);
}

void CSoundMgr::StopAll()
{
	for (int i = 0; i < END; ++i)
		FMOD_Channel_Stop(m_pChannel[i]);
}

FMOD_BOOL CSoundMgr::IsPlayingCheck(CHANNEL_ID eID)
{
	FMOD_Channel_IsPlaying(m_pChannel[eID], &IsPlaying);

	return IsPlaying;
}

void CSoundMgr::LoadSoundFile()
{
	_finddata_t fd;
	int handle = _findfirst("Sound/*.*", &fd);

	if (0 == handle)
		return;

	char szFullPath[256] = "";
	int iContinue = 0;

	while (-1 != iContinue)
	{
		strcpy_s(szFullPath, "Sound/");
		strcat_s(szFullPath, fd.name);

		FMOD_SOUND* pSound = nullptr;

		FMOD_RESULT res = FMOD_System_CreateSound(m_pSystem,
			szFullPath, FMOD_HARDWARE, nullptr, &pSound);

		if (FMOD_OK == res)
		{
			string strSoundKey = string(fd.name);

			auto iter_find = m_mapSound.find(strSoundKey);

			if (m_mapSound.end() != iter_find)
			{
				FMOD_Sound_Release(pSound);
				continue;
			}

			m_mapSound[strSoundKey] = pSound;
		}

		iContinue = _findnext(handle, &fd);
	}

	FMOD_System_Update(m_pSystem);
}

void CSoundMgr::Release()
{
	for (auto& MyPair : m_mapSound)
		FMOD_Sound_Release(MyPair.second);

	m_mapSound.clear();

	FMOD_System_Release(m_pSystem);
	FMOD_System_Close(m_pSystem);
}
