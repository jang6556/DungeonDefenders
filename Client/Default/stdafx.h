// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <io.h>
#include <process.h>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include "ComponentMgr.h"
#include "GameObjectMgr.h"
#include "RenderTargetMgr.h"
#include "ManageMent.h"
#include "InputDev.h"
#include "LightMgr.h"
#include "../Header/Define.h"

#include "Bullet.h"
#include "Monster.h"
#include "MonsterUI.h"
#include "Player.h"
#include "Tower.h"
#include "MonsterController.h"
#include "StatPanel.h"
#include "Crystal.h"
#include "Decal.h"



#include "../Default/fmod.h"
#include "SoundMgr.h"
#pragma comment(lib, "fmodex_vc.lib")

#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
