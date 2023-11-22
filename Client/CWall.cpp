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
	if (_OtherObj->GetName() == L"GiantSword")
		return;

	if (_OtherObj->GetLayerIdx() == (UINT)LAYER::PROJECTILE)
		return;



	
	Vec2 vPos = _OwnCol->GetPos();
	Vec2 vObjPos = _OtherObj->GetPos();
	CMovement* pOtherMovement = _OtherObj->GetComponent<CMovement>();

	if (m_pCollider->GetAngle() == 0.f)
	{
		// 왼쪽으로 충돌했을 경우
		if (vPos.x > vObjPos.x && (pOtherMovement->GetVelocity().x > 0))
		{
			_OtherObj->SetPos(Vec2(vPos.x - _OwnCol->GetScale().x / 2.f - _OtherCol->GetScale().x / 2.f, vObjPos.y));
		}

		// 오른쪽으로 충돌했을 경우
		if (vPos.x < vObjPos.x && (pOtherMovement->GetVelocity().x < 0))
		{
			_OtherObj->SetPos(Vec2(vPos.x + _OwnCol->GetScale().x / 2.f + _OtherCol->GetScale().x / 2.f, vObjPos.y));
		}
	}


}


