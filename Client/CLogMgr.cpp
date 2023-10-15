#include "pch.h"
#include "CLogMgr.h"

#include "CTimeMgr.h"
#include "CEngine.h"

CLogMgr::CLogMgr()
	: m_fLogMaxLife(5.f)
{

}

CLogMgr::~CLogMgr()
{

}


void CLogMgr::tick()
{
	list<FLog>::iterator iter = m_LogList.begin();

	for (; iter != m_LogList.end(); )
	{
		(*iter).AccTime += DT;
		if (m_fLogMaxLife < (*iter).AccTime)
		{
			iter = m_LogList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CLogMgr::render(HDC _dc)
{
	if (!DEBUG_RENDER)
		return;

	list<FLog>::iterator iter = m_LogList.begin();

	iter = m_LogList.begin();
	POINT LT = { 10, 10 };

	int idx = 0;

	for (; iter != m_LogList.end(); ++iter, ++idx)
	{
		switch ((*iter).Level)
		{
		case LOG_LEVEL::LOG:
			SetTextColor(_dc, RGB(0, 0, 0));
			break;
		case LOG_LEVEL::WARNING:
			SetTextColor(_dc, RGB(210, 210, 153));
			break;
		case LOG_LEVEL::ERR:
			SetTextColor(_dc, RGB(255, 0, 0));
			break;
		}

		TextOut(_dc, LT.x, LT.y + idx * int(10.f * 1.5f), (*iter).Message.c_str(), int((*iter).Message.length()) );
	}

}
