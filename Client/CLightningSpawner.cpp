#include "pch.h"
#include "CLightningSpawner.h"


#include "CEngine.h"
#include "CLevelMgr.h"
#include "CPenitent.h"

#include "CLightning.h"

CLightningSpawner::CLightningSpawner()
	: m_bIsOn(false)
	, m_fLifeTime(9.f)
	, m_fAcc(0.f)
	, m_vecLightning{}
	, m_fCooltime(0.f)
	, m_iCurLightning(0)
	, m_iPrevLightnigActive(2)
{
	m_pTarget = CLevelMgr::GetInst()->GetPenitent();
}

CLightningSpawner::~CLightningSpawner()
{
}


void CLightningSpawner::On(Vec2 _vPos)
{
	SetPos(Vec2(_vPos.x, _vPos.y - 500.f));

	m_fAcc = 0.f;
	m_iCurLightning = 0;
	m_bIsOn = true;
	m_fCooltime = 0.f;
	m_iPrevLightnigActive = 2;

}

void CLightningSpawner::Off()
{
	SetPos(Vec2(0.f, 0.f));
	m_bIsOn = false;
}

void CLightningSpawner::tick(float _DT)
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


		if (m_fCooltime > 2.f)
		{
			if (m_iCurLightning < m_vecLightning.size())
			{
				Vec2 vTargetDir = m_pTarget->GetPos();

				if (m_iPrevLightnigActive == 2)
				{
					m_vecLightning[m_iCurLightning]->On(vTargetDir);
					m_iPrevLightnigActive = 1;
					++m_iCurLightning;
				}
				else
				{
					if (m_vecLightning.size() - m_iCurLightning > 1)
					{
						Vec2 Offset = Vec2(70.f, 0.f);
						m_vecLightning[m_iCurLightning]->On(vTargetDir + Offset);
						m_vecLightning[m_iCurLightning + 1]->On(vTargetDir - Offset);
						m_iPrevLightnigActive = 2;
						m_iCurLightning += 2;
					}
				}
				m_fCooltime = 0.f;
			}
		}

	}

}

void CLightningSpawner::render(HDC _dc)
{
	Super::render(_dc);

	if (!DEBUG_RENDER)
		return;

	if (!m_bIsOn)
		return;


}

