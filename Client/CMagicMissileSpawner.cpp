#include "pch.h"
#include "CMagicMissileSpawner.h"

#include "CEngine.h"

#include "CMagicMissile.h"

CMagicMissileSpawner::CMagicMissileSpawner()
	: m_bIsOn(false)
	, m_bDir(true)
	, m_fLifeTime(6.f)
	, m_fCooltime(0.f)
	, m_fAcc(0.f)
	, m_vecMagicMissile{}
	, m_iCurMagic(0)
	, m_bPrevUP(false)
{
}

CMagicMissileSpawner::~CMagicMissileSpawner()
{
}


void CMagicMissileSpawner::On(Vec2 _vPos, bool _bDir)
{
	SetPos(Vec2(_vPos.x, _vPos.y - 80.f));

	m_fAcc = 0.f;
	m_iCurMagic = 0;
	m_bIsOn = true;
	m_fCooltime = 0.f;
	m_bDir = _bDir;
	m_bPrevUP = false;

}

void CMagicMissileSpawner::Off()
{
	SetPos(Vec2(0.f, 0.f));
	m_bIsOn = false;

}

void CMagicMissileSpawner::tick(float _DT)
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


		if (m_fCooltime > 0.7f)
		{
			if (m_iCurMagic < m_vecMagicMissile.size())
			{
				Vec2 vPos = GetPos();

				// 마지막으로 나간게 위
				if (m_bPrevUP)
				{
					vPos.y += 40.f;
					m_bPrevUP = false;
				}
				// 아래
				else
				{
					vPos.y -= 50.f;
					m_bPrevUP = true;
				}

				if (m_bDir)
				{
					m_vecMagicMissile[m_iCurMagic]->On(vPos, Vec2(1.f,0.f));
				}
				else
				{
					m_vecMagicMissile[m_iCurMagic]->On(vPos, Vec2(-1.f, 0.f));
				}

				m_fCooltime = 0.f;
				m_iCurMagic++;
			}
		}

	}

}

void CMagicMissileSpawner::render(HDC _dc)
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
		, int(vRenderPos.y - 50.f)
		, int(vRenderPos.x + 20.f)
		, int(vRenderPos.y + 40.f));

}

