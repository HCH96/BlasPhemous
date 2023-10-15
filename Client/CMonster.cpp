#include "pch.h"
#include "CMonster.h"

#include "components.h"

#include "CProjectile.h"

CMonster::CMonster()
	: m_Info{}
	, m_pCollider(nullptr)
{
	m_pCollider = AddComponent<CCollider>(L"MonsterCollider");
	m_Info.HP = 5;
}

CMonster::~CMonster()
{
}

void CMonster::begin()
{
	m_pCollider->SetScale(GetScale() - 10.f);
}

void CMonster::tick(float _DT)
{
	Super::tick(_DT);
}

void CMonster::render(HDC _dc)
{
	Vec2 vRenderPos = GetRenderPos();
	Vec2 vScale = GetScale();

	Rectangle(_dc
		, int(vRenderPos.x - vScale.x / 2)
		, int(vRenderPos.y - vScale.y / 2)
		, int(vRenderPos.x + vScale.x / 2)
		, int(vRenderPos.y + vScale.y / 2));

	Super::render(_dc);
}


void CMonster::BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol)
{
	if (dynamic_cast<CProjectile*>(_pOtherObj))
	{
		m_Info.HP -= 1.f;

		if (m_Info.HP <= 0.f)
		{
			Destroy();
		}
	}

}