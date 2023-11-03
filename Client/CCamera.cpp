#include "pch.h"
#include "CCamera.h"

#include "CEngine.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CAssetMgr.h"

#include "CTexture.h"

CCamera::CCamera()
	: m_pVeil(nullptr)
	, m_Alpha(0)
{
	Vec2 vResol = CEngine::GetInst()->GetResolution();
	m_pVeil = CAssetMgr::GetInst()->CreateTexture(L"VeilTex", (int)vResol.x, (int)vResol.y);
}

CCamera::~CCamera()
{

}

void CCamera::tick()
{
	 //방향키로 카메라가 바라보고 있는 위치를 변경
	//if (KEY_PRESSED(KEY::LEFT))
	//{
	//	m_vLookAt.x -= 200.f * DT;
	//}

	//if (KEY_PRESSED(KEY::RIGHT))
	//{
	//	m_vLookAt.x += 200.f * DT;
	//}

	//if (KEY_PRESSED(KEY::UP))
	//{
	//	m_vLookAt.y -= 200.f * DT;
	//}

	//if (KEY_PRESSED(KEY::DOWN))
	//{
	//	m_vLookAt.y += 200.f * DT;
	//}

	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2.f;

	m_vDiff = m_vLookAt - vCenter;


	// 카메라 이벤트가 없으면 리턴
	if (m_EventList.empty())
		return;

	// 카메라 이벤트가 존재한다면
	FCamEvent& evnt = m_EventList.front();

	if (evnt.Type == CAM_EFFECT::FADE_IN)
	{
		evnt.AccTime += DT;

		if (evnt.Duration <= evnt.AccTime)
		{
			m_Alpha = 0;
			m_EventList.pop_front();
		}
		else
		{
			float fRatio = evnt.AccTime / evnt.Duration;
			float alpha = 1.f - fRatio;
			m_Alpha = (UINT)(alpha * 255);
		}
	}

	else if (evnt.Type == CAM_EFFECT::FADE_OUT)
	{
		evnt.AccTime += DT;

		if (evnt.Duration <= evnt.AccTime)
		{
			m_EventList.pop_front();
			m_Alpha = 255;
		}
		else
		{
			float fRatio = evnt.AccTime / evnt.Duration;
			float alpha = fRatio;
			m_Alpha = (UINT)(alpha * 255);
		}
	}
}

void CCamera::render(HDC _dc)
{
	if (0 == m_Alpha)
		return;

	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;

	blend.SourceConstantAlpha = m_Alpha; // 0 ~ 255
	blend.AlphaFormat = 0; // 0

	AlphaBlend(_dc
		, 0, 0, m_pVeil->GetWidth(), m_pVeil->GetHeight()
		, m_pVeil->GetDC()
		, 0, 0
		, m_pVeil->GetWidth(), m_pVeil->GetHeight()
		, blend);

}
