// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <io.h>
#include <process.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
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
