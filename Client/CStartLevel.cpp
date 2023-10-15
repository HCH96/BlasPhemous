#include "pch.h"
#include "CStartLevel.h"

#include "CKeyMgr.h"

void CStartLevel::init()
{
}

void CStartLevel::enter()
{
}

void CStartLevel::exit()
{
}

void CStartLevel::tick()
{
	CLevel::tick();

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::PLAY_LEVEL);
	}
}
