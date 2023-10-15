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

#pragma comment(lib, "Msimg32.lib")

#include <assert.h>

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
