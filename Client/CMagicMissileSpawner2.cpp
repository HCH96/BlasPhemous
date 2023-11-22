#include "pch.h"
#include "CMagicMissileSpawner2.h"

#include "CEngine.h"
#include "CMagicMissile.h"


CMagicMissileSpawner2::CMagicMissileSpawner2()
{
}

CMagicMissileSpawner2::~CMagicMissileSpawner2()
{
}


void CMagicMissileSpawner2::On(Vec2 _vPos)
{
	SetPos(_vPos);

	m_bIsOn = true;
}

void CMagicMissileSpawner2::Off()
{
	SetPos(Vec2(0.f, 0.f));
	m_bIsOn = false;

}

void CMagicMissileSpawner2::tick(float _DT)
{
	Super::tick(_DT);
	Vec2 vPos = GetPos();

	if (m_bIsOn)
	{
		float fAngle = 0.f;
		for (int i = 0; i < m_vecMagicMissile.size(); ++i)
		{
			m_vecMagicMissile[i]->On(vPos, Vec2(1.f, 0.f).Rotate(fAngle));
			fAngle += 60.f;

		}
	}

	

	Off();
}

void CMagicMissileSpawner2::render(HDC _dc)
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

