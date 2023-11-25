#include "pch.h"
#include "CCamera.h"

#include "CEngine.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CAssetMgr.h"

#include "CTexture.h"

#include "CObj.h"
#include "CPenitent.h"
#include "CLevelMgr.h"

CCamera::CCamera()
	: m_pVeil(nullptr)
	, m_pTarget(nullptr)
	, m_Alpha(0)
	, m_vCameraLimitLT(0.f, 0.f)
	, m_vCameraLimit(12800.f,7200.f)
	, m_vTarget(Vec2(0.f,0.f))
	, m_fShakeIntensity(0.f)
	, m_pDeathScreen(nullptr)
{
	Vec2 vResol = CEngine::GetInst()->GetResolution();
	m_pVeil = CAssetMgr::GetInst()->CreateTexture(L"VeilTex", (int)vResol.x, (int)vResol.y);

	m_pDeathScreen = CAssetMgr::GetInst()->LoadTexture(L"DeathScreen", L"texture\\UI\\Death_Screen.png");
	m_pBossClear = CAssetMgr::GetInst()->LoadTexture(L"BossClear", L"texture\\UI\\boss-defeated-screen-title.png");
}

CCamera::~CCamera()
{

}

void CCamera::SetTarget(CObj* _pTarget)
{
	if (_pTarget == nullptr)
	{
		m_pTarget = nullptr;
		return;
	}

	 m_pTarget = _pTarget; 
	 InitLookAt(_pTarget->GetPos()); 
}

void CCamera::tick()
{
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2.f;

	// LookAt ����
	if (IsValid(m_pTarget))
	{
		// Target�� Penitent�ϰ��
		if (dynamic_cast<CPenitent*>(m_pTarget))
		{
			bool bDir = m_pTarget->GetDir();

			// �������� �Ĵٺ��� �ִ� ���
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



	// ���� LookAt�� ���� Look�� ���̰��� �����ؼ� ������ LookAt�� ���Ѵ�.
	Vec2 vLookDir = m_vLookAt - m_vPrevLookAt;
	float fSpeed = vLookDir.Length() * 3.f;


	// ���� ������ ī�޶��� ��ġ���� �̵��ؾ��ϴ� �������� ī�޶��� CurLookAt�� ���
	if (!vLookDir.IsZero())
	{
		m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * fSpeed * 1.5f * DT;
	}

	if ((m_vCurLookAt - m_vLookAt).Length() < 0.1f)
	{
		m_vCurLookAt = m_vLookAt;
	}

	// ī�޶� ���������� �Ѿ�ٸ�

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

	

	// ī�޶� �̺�Ʈ ����

	// ī�޶� �̺�Ʈ�� ������ ����
	if (m_EventList.empty())
	{
		// Diff ���
		m_vDiff = m_vCurLookAt - vCenter;

		// PrevLookAt ����
		m_vPrevLookAt = m_vCurLookAt;
		return;
	}

	// ī�޶� �̺�Ʈ�� �����Ѵٸ�
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
	else if (evnt.Type == CAM_EFFECT::DEATH)
	{
		evnt.AccTime += DT;

		if (m_Alpha < 255.f)
		{
			float fRatio = evnt.AccTime / evnt.Duration;
			if (fRatio > 1.f)
			{
				fRatio = 1.f;
			}

			float alpha = fRatio;
			m_Alpha = (UINT)(alpha * 255);
		}
		else
		{
			m_Alpha = 255;

			if (KEY_TAP(KEY::ENTER))
			{
				CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();
				UINT iCheckPoint = pPenitent->GetCheckPont();

				::ChangeLevel((LEVEL_TYPE)iCheckPoint);

				m_EventList.pop_front();
			}


		}


	}
	else if (evnt.Type == CAM_EFFECT::BOSS_CLEAR)
	{
		evnt.AccTime += DT;

		// ���� ����
		if (m_bInEvent == false && m_Alpha <= 0.f)
		{
			m_bInClear = false;
			m_EventList.pop_front();
		}
		// excute
		else
		{
			if (m_bInEvent)
			{
				float fRatio = evnt.AccTime / evnt.Duration;
				float alpha = fRatio;

				if (alpha >= 1.f)
					alpha = 1.f;

				m_Alpha = (UINT)(alpha * 255);
				
			}
			else
			{
				float fRatio = evnt.AccTime / evnt.Duration;
				float alpha = 1.f - fRatio;

				if (alpha <= 0.f)
					alpha = 0.f;

				m_Alpha = (UINT)(alpha * 255);
			}

			if (m_Alpha == 255 && KEY_TAP(KEY::ENTER))
			{
				m_bInEvent = false;
				evnt.AccTime = 0.f;
			}

			
		}

	}


	// Diff ���
	m_vDiff = m_vCurLookAt - vCenter;

	// PrevLookAt ����
	m_vPrevLookAt = m_vCurLookAt;
}

void CCamera::render(HDC _dc)
{
	if (0 == m_Alpha)
		return;

	if (!m_bInClear)
	{
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

	

	if (m_EventList.empty())
		return;

	FCamEvent& evnt = m_EventList.front();

	if (evnt.Type == CAM_EFFECT::DEATH)
	{
		BLENDFUNCTION blend = {};
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;

		blend.SourceConstantAlpha = m_Alpha; // 0 ~ 255
		blend.AlphaFormat = 0; // 0

		AlphaBlend(_dc
			, 0, 0
			, 1280, 720
			, m_pDeathScreen->GetDC()
			, 0, 0
			, m_pDeathScreen->GetWidth(), m_pDeathScreen->GetHeight()
			, blend);

		return;
	}

	if (evnt.Type == CAM_EFFECT::BOSS_CLEAR)
	{
		BLENDFUNCTION blend = {};
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;

		blend.SourceConstantAlpha = m_Alpha; // 0 ~ 255
		blend.AlphaFormat = AC_SRC_ALPHA; // 0

		AlphaBlend(_dc
			, 308, 158
			, m_pBossClear->GetWidth() * 2, m_pBossClear->GetHeight() * 2
			, m_pBossClear->GetDC()
			, 0, 0
			, m_pBossClear->GetWidth(), m_pBossClear->GetHeight()
			, blend);

		return;
	}

		




}
