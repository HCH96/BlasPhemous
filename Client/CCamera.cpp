#include "pch.h"
#include "CCamera.h"

#include "CEngine.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CAssetMgr.h"

#include "CTexture.h"

#include "CObj.h"
#include "CPenitent.h"

CCamera::CCamera()
	: m_pVeil(nullptr)
	, m_pTarget(nullptr)
	, m_Alpha(0)
	, m_vCameraLimitLT(0.f, 0.f)
	, m_vCameraLimit(12800.f,7200.f)
	, m_vTarget(Vec2(0.f,0.f))
	, m_fShakeIntensity(0.f)
{
	Vec2 vResol = CEngine::GetInst()->GetResolution();
	m_pVeil = CAssetMgr::GetInst()->CreateTexture(L"VeilTex", (int)vResol.x, (int)vResol.y);
}

CCamera::~CCamera()
{

}

void CCamera::SetTarget(CObj* _pTarget)
{
	 m_pTarget = _pTarget; 
	 InitLookAt(_pTarget->GetPos()); 
}

void CCamera::tick()
{
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2.f;

	// LookAt 설정
	if (IsValid(m_pTarget))
	{
		// Target이 Penitent일경우
		if (dynamic_cast<CPenitent*>(m_pTarget))
		{
			bool bDir = m_pTarget->GetDir();

			// 오른쪽을 쳐다보고 있는 경우
			if (bDir)
			{
				m_vLookAt = m_pTarget->GetPos() + m_vLookAtOffset;
			}
			else
			{
				m_vLookAt = m_pTarget->GetPos() + (m_vLookAtOffset * Vec2(-1.f, 1.f));
			}

		}
		else
		{
			m_vLookAt = m_pTarget->GetPos();
		}
	}
	else
	{
		m_pTarget = nullptr;
	}


	// DEBUG
	//if (KEY_PRESSED(KEY::LEFT))
	//{
	//	m_vLookAt.x -= 500.f * DT;
	//}

	//if (KEY_PRESSED(KEY::RIGHT))
	//{
	//	m_vLookAt.x += 500.f * DT;
	//}

	//if (KEY_PRESSED(KEY::UP))
	//{
	//	m_vLookAt.y -= 500.f * DT;
	//}

	//if (KEY_PRESSED(KEY::DOWN))
	//{
	//	m_vLookAt.y += 500.f * DT;
	//}



	// 이전 LookAt과 현재 Look의 차이값을 보정해서 현재의 LookAt을 구한다.
	Vec2 vLookDir = m_vLookAt - m_vPrevLookAt;
	float fSpeed = vLookDir.Length() * 3.f;


	// 이전 프레임 카메라의 위치에서 이동해야하는 방향으로 카메라의 CurLookAt을 등록
	if (!vLookDir.IsZero())
	{
		m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * fSpeed * 1.5f * DT;
	}

	if ((m_vCurLookAt - m_vLookAt).Length() < 0.1f)
	{
		m_vCurLookAt = m_vLookAt;
	}

	// 카메라가 제한지점을 넘어갔다면

	// LEFT
	if (m_vCurLookAt.x - vResolution.x / 2.f < m_vCameraLimitLT.x)
	{
		m_vCurLookAt.x = m_vCameraLimitLT.x + vResolution.x / 2.f;
	}

	// RIGHT
	if (m_vCurLookAt.x + vResolution.x / 2.f > m_vCameraLimit.x)
	{
		m_vCurLookAt.x = m_vCameraLimit.x - vResolution.x / 2.f;
	}

	// TOP
	if (m_vCurLookAt.y - vResolution.y / 2.f < m_vCameraLimitLT.y)
	{
		m_vCurLookAt.y = m_vCameraLimitLT.y + vResolution.y / 2.f;
	}

	// BOTTOM
	if (m_vCurLookAt.y + vResolution.y / 2.f > m_vCameraLimit.y)
	{
		m_vCurLookAt.y = m_vCameraLimit.y - vResolution.y / 2.f;
	}

	

	// 카메라 이벤트 설정

	// 카메라 이벤트가 없으면 리턴
	if (m_EventList.empty())
	{
		// Diff 계산
		m_vDiff = m_vCurLookAt - vCenter;

		// PrevLookAt 저장
		m_vPrevLookAt = m_vCurLookAt;
		return;
	}

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
			LEVEL_TYPE eNextType = evnt.NextLevel;
			m_EventList.pop_front();
			m_Alpha = 255;
			if (evnt.NextLevel != LEVEL_TYPE::END)
			{
				::ChangeLevel(eNextType);
			}
		}
		else
		{
			float fRatio = evnt.AccTime / evnt.Duration;
			float alpha = fRatio;
			m_Alpha = (UINT)(alpha * 255);
		}
	}
	else if (evnt.Type == CAM_EFFECT::SHAKE)
	{
		evnt.AccTime += DT;

		if (evnt.Duration <= evnt.AccTime)
		{
			m_fShakeIntensity = 0.f;
			m_vTarget = Vec2(0.f, 0.f);
			m_EventList.pop_front(); 
		}
		else
		{
			float offsetX = (rand() % 100 - 50) * m_fShakeIntensity;
			float offsetY = (rand() % 10 - 5) * m_fShakeIntensity;

			m_vTarget.x = m_vCurLookAt.x + offsetX;
			m_vTarget.y = m_vCurLookAt.y + offsetY;

			m_vCurLookAt.x = lerp(m_vCurLookAt.x, m_vTarget.x, 0.5f);
			m_vCurLookAt.y = lerp(m_vCurLookAt.y, m_vTarget.y, 0.5f);

		}
	}


	// Diff 계산
	m_vDiff = m_vCurLookAt - vCenter;

	// PrevLookAt 저장
	m_vPrevLookAt = m_vCurLookAt;
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
