#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����
#include <windows.h>
// C ��Ÿ�� ��� �����Դϴ�.
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

// ����
#include <assert.h>

// ����
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
