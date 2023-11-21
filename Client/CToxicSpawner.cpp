#include "pch.h"
#include "CToxicSpawner.h"

#include "CToxic.h"
#include "CEngine.h"

CToxicSpawner::CToxicSpawner()
	: m_bIsOn(false)
	, m_fLifeTime(8.f)
	, m_fAcc(0.f)
	, m_vecCToxic{}
	, m_fCooltime(0.f)
	, m_iCurToxic(0)
{
}

CToxicSpawner::~CToxicSpawner()
{
}

void CToxicSpawner::On(Vec2 _vPos)
{
	SetPos(Vec2(_vPos.x, _vPos.y - 500.f));

	m_fAcc = 0.f;
	m_iCurToxic = 0;
	m_bIsOn = true;
	m_fCooltime = 0.f;

}

void CToxicSpawner::Off()
{
	SetPos(Vec2(0.f, 0.f));
	m_bIsOn = false;



}

void CToxicSpawner::tick(float _DT)
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
			if (m_iCurToxic < m_vecCToxic.size())
			{
				Vec2 vPos = GetPos();

				vPos.x = vPos.x + (rand() % 1000 - 500);

				m_vecCToxic[m_iCurToxic]->On(vPos);
				m_fCooltime = 0.f;
				m_iCurToxic++;
			}
		}

	}

}

void CToxicSpawner::render(HDC _dc)
{
	Super::render(_dc);

	if (!DEBUG_RENDER)
		return;

	if (!m_bIsOn)
		return;

	SELECT_PEN(_dc, PEN_TYPE::RED);

	Vec2 vRenderPos = GetRenderPos();
	Rectangle(_dc
		, int(vRenderPos.x - 500.f)
		, int(vRenderPos.y - 20.f)
		, int(vRenderPos.x + 500.f)
		, int(vRenderPos.y + 20.f));

}

