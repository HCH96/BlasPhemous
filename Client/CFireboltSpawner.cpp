#include "pch.h"
#include "CFireboltSpawner.h"

#include "CEngine.h"
#include "CPenitent.h"
#include "CLevelMgr.h"

#include "CFirebolt.h"

CFireboltSpawner::CFireboltSpawner()
	: m_bIsOn(false)
	, m_fLifeTime(6.f)
	, m_fAcc(0.f)
	, m_vecFirebolt{}
	, m_fCooltime(0.f)
	, m_iCurFire(0)
{
	m_pTarget = CLevelMgr::GetInst()->GetPenitent();
}

CFireboltSpawner::~CFireboltSpawner()
{
}


void CFireboltSpawner::On(Vec2 _vPos)
{
	SetPos(Vec2(_vPos.x, _vPos.y-500.f));

	m_fAcc = 0.f;
	m_iCurFire = 0;
	m_bIsOn = true;
	m_fCooltime = 0.f;
}

void CFireboltSpawner::Off()
{
	SetPos(Vec2(0.f, 0.f));
	m_bIsOn = false;
}

void CFireboltSpawner::tick(float _DT)
{
	Super::tick(_DT);
	
	if (!m_bIsOn)
	{
		return;
	}

	if (m_fAcc > m_fLifeTime)
	{
		Off();
	}
	else
	{
		m_fAcc += _DT;
		m_fCooltime += _DT;


		if (m_fCooltime > 0.6f)
		{
			if (m_iCurFire < m_vecFirebolt.size())
			{
				Vec2 vPos = GetPos();
				Vec2 vTargetDir = m_pTarget->GetPos();
				vTargetDir.y -= 100.f;
				Vec2 vDir = (vTargetDir - vPos).Normalize();

				m_vecFirebolt[m_iCurFire]->On(GetPos(), vDir);
				m_fCooltime = 0.f;
				m_iCurFire++;
			}
		}

	}
}

void CFireboltSpawner::render(HDC _dc)
{
	Super::render(_dc);

	if (!DEBUG_RENDER)
		return;

	if (!m_bIsOn)
		return;

	SELECT_PEN(_dc, PEN_TYPE::GREEN);

	Vec2 vRenderPos = GetRenderPos();
	Rectangle(_dc
		, int(vRenderPos.x - 20.f)
		, int(vRenderPos.y - 20.f)
		, int(vRenderPos.x + 20.f)
		, int(vRenderPos.y + 20.f));


}
