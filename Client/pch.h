#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// render
#pragma comment(lib, "Msimg32.lib")

// png
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")

using namespace::Gdiplus;

// 오류
#include <assert.h>

// 사운드
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

// std
#include <vector>
#include <list>
#include <string>
#include <map>

using std::vector;
using std::list;
using std::string;
using std::map;
using std::make_pair;
using std::wstring;

#include "global.h"
