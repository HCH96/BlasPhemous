#include "pch.h"
#include "CLightningSpawner2.h"

#include "CLightning.h"
#include "CEngine.h"


CLightningSpawner2::CLightningSpawner2()
	: m_bIsOn(false)
	, m_fLifeTime(9.f)
	, m_fAcc(0.f)
	, m_vecLightning{}
	, m_fCooltime(0.f)
	, m_iCurLightning(0)
	, m_bDir(true)
{
}

CLightningSpawner2::~CLightningSpawner2()
{
}


void CLightningSpawner2::On(Vec2 _vPos, bool _bDir)
{
	SetPos(_vPos);

	m_fAcc = 0.f;
	m_iCurLightning = 0;
	m_bIsOn = true;
	m_fCooltime = 0.f;
	m_bDir = _bDir;

}

void CLightningSpawner2::Off()
{
	SetPos(Vec2(0.f, 0.f));
	m_bIsOn = false;

}

void CLightningSpawner2::tick(float _DT)
{
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


		if (m_fCooltime > 0.15f && m_iCurLightning < m_vecLightning.size())
		{
			Vec2 vPos = GetPos();
			if (m_bDir)
			{
				vPos += Vec2(120.f, 0.f) * m_iCurLightning;
			}
			else
			{
				vPos += Vec2(-120.f, 0.f) * m_iCurLightning;
			}

			m_vecLightning[m_iCurLightning]->On(vPos);

			++m_iCurLightning;
			m_fCooltime = 0.f;
		}
	}

	if (m_fAcc > 5.f)
		Off();

}

void CLightningSpawner2::render(HDC _dc)
{
	Super::render(_dc);

	if (!DEBUG_RENDER)
		return;

	if (!m_bIsOn)
		return;


}
