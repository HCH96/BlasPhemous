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
				m_vLookAt = m_pTarget->GetPos() + (m_vLookAtOffset * Vec2(-1.f,1.f));
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


	

	// ���� LookAt�� ���� Look�� ���̰��� �����ؼ� ������ LookAt�� ���Ѵ�.
	Vec2 vLookDir = m_vLookAt - m_vPrevLookAt;
	float fSpeed = vLookDir.Length();

	// ���� ������ ī�޶��� ��ġ���� �̵��ؾ��ϴ� �������� ī�޶��� CurLookAt�� ���
	if (!vLookDir.IsZero())
	{
		m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * fSpeed * 8 * DT;
	}

	// ī�޶� ���������� �Ѿ�ٸ�
	if (m_vCurLookAt.x - vResolution.x/2.f < 0 || m_vCurLookAt.x + vResolution.x / 2.f > m_vCameraLimit.x)
	{
		m_vCurLookAt.x = m_vPrevLookAt.x;
	}
	if (m_vCurLookAt.y - vResolution.y / 2.f < 0 || m_vCurLookAt.y + vResolution.y / 2.f > m_vCameraLimit.y)
	{
		m_vCurLookAt.y = m_vPrevLookAt.y;
	}



	// Diff ���
	m_vDiff = m_vCurLookAt - vCenter;

	// PrevLookAt ����
	m_vPrevLookAt = m_vCurLookAt;


	// ī�޶� �̺�Ʈ ����

	// ī�޶� �̺�Ʈ�� ������ ����
	if (m_EventList.empty())
		return;

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
