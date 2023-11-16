#include "pch.h"
#include "CTimeMgr.h"

#include "CEngine.h"

CTimeMgr::CTimeMgr()
	: m_llFrequency{}
	, m_llPrevCount{}
	, m_llCurCount{}
	, m_fDeltaTime(0.f)
	, m_fTime(0.f)
	, m_iCall(0)
	, m_bDelay(false)
	, m_fDelayTime(0.05f)
	, m_fDelayAcc(0.f)
{
}

CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::Delay()
{
	m_bDelay = true;
}

void CTimeMgr::init()
{
	// 초당 빈도수
	QueryPerformanceFrequency(&m_llFrequency);
	QueryPerformanceCounter(&m_llPrevCount);
}

void CTimeMgr::tick()
{
	QueryPerformanceCounter(&m_llCurCount);

	m_fDeltaTime = float(m_llCurCount.QuadPart - m_llPrevCount.QuadPart)/ float(m_llFrequency.QuadPart);


	//DT 보정
	if (m_fDeltaTime > (1.f / 60.f))
	{
		m_fDeltaTime = 1.f / 60.f;
	}


	m_fTime += m_fDeltaTime;

	if (m_fTime>= 1.f)
	{
		wchar_t szText[50] = {};
		swprintf_s(szText, 50, L"DeltaTime : %f, FPS : %d", m_fDeltaTime, m_iCall);

		SetWindowText(CEngine::GetInst()->GetMainWind(), szText);

		m_fTime = 0.f;
		m_iCall= 0;
	}

	if (m_bDelay)
	{
		m_fDelayAcc += m_fDeltaTime;
		m_fDeltaTime = 0.f;

		if (m_fDelayAcc > m_fDelayTime)
		{
			m_fDelayAcc = 0.f;
			m_bDelay = false;
		}
	}

	m_llPrevCount = m_llCurCount;
	++m_iCall;
}
