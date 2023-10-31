#include "pch.h"
#include "CProjectile.h"

#include "CCollider.h"
#include "CMonster.h"


CProjectile::CProjectile()
	: m_fSpeed(0.f)
	, m_fTheta(0.f)
	, m_pCollider(nullptr)
{
	m_pCollider = AddComponent<CCollider>(L"Collider");
}

CProjectile::CProjectile(const CProjectile& _Origin)
	: m_pCollider(nullptr)
	, m_fSpeed(_Origin.m_fSpeed)
	, m_fTheta(_Origin.m_fTheta)
{
	m_pCollider = GetComponent<CCollider>();

}

CProjectile::~CProjectile()
{
}



void CProjectile::begin()
{
	Super::begin();

	GetCollider()->SetScale(GetScale());
}

void CProjectile::tick(float _DT)
{
	Super::tick(_DT);

	Vec2 vPos = GetPos();

	vPos.x += m_fSpeed * cosf(m_fTheta) * _DT;
	vPos.y -= m_fSpeed * sinf(m_fTheta) * _DT;

	SetPos(vPos);
}

void CProjectile::render(HDC _dc)
{

	Vec2 vPos = GetRenderPos();
	Vec2 vScale = GetScale();

	Ellipse(_dc
		, int(vPos.x - vScale.x / 2)
		, int(vPos.y - vScale.y / 2)
		, int(vPos.x + vScale.x / 2)
		, int(vPos.y + vScale.y / 2));

	Super::render(_dc);
}

void CProjectile::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if (dynamic_cast<CMonster*>(_OtherObj))
	{
		Destroy();
	}
}

