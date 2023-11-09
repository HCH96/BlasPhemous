#include "pch.h"
#include "CWall.h"

#include "CComponent.h"

CWall::CWall()
	: m_pCollider(nullptr)
{
	m_pCollider = AddComponent<CCollider>();
	m_pCollider->SetOffsetPos(Vec2(0.f, 0.f));

}

CWall::CWall(const CWall& _Origin)
	: CObj(_Origin)
	, m_pCollider(nullptr)
{
	m_pCollider = GetComponent<CCollider>();
}

CWall::~CWall()
{
}


void CWall::begin()
{
	m_pCollider->SetScale(GetScale());
}


void CWall::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	
	Vec2 vPos = _OwnCol->GetPos();
	Vec2 vScale = _OwnCol->GetScale();
	Vec2 vOtherPos = _OtherObj->GetPos();
	Vec2 vOtherScale = _OtherCol->GetScale();

	// 오른쪽에 오브젝트 있음
	if (vPos.x - vOtherPos.x < 0)
	{
		_OtherObj->SetPos(Vec2(vPos.x + vScale.x/2.f + vOtherScale.x/2.f +1.f , vOtherPos.y));
	}

	// 왼쪽에 오브젝트 있음
	if (vPos.x - vOtherPos.x > 0)
	{
		_OtherObj->SetPos(Vec2(vPos.x - vScale.x / 2.f - vOtherScale.x / 2.f -1.f, vOtherPos.y));
	}

}


