#include "pch.h"
#include "CPlatform.h"

#include "components.h"

#include "CPenitent.h"

CPlatform::CPlatform()
{
	m_pCollider = AddComponent<CCollider>(L"Collider");
	m_pCollider->SetOffsetPos(Vec2(0.f,0.f));
	
}

CPlatform::CPlatform(const CPlatform& _Origin)
	: CObj(_Origin)
	, m_pCollider(nullptr)
{
	m_pCollider = GetComponent<CCollider>();
}

CPlatform::~CPlatform()
{

}


void CPlatform::begin()
{
	m_pCollider->SetScale(GetScale());
}


void CPlatform::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	Vec2 vPos = _OwnCol->GetPos();
	Vec2 vObjPos = _OtherObj->GetPos();
	CMovement* pOtherMovement = _OtherObj->GetComponent<CMovement>();


	// 옆면 충돌했을 경우
	if (m_pCollider->GetAngle() == 0.f && _OtherObj->GetPos().y > _OwnCol->GetPos().y + 10.f)
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
	else
	{
		float fAngle = m_pCollider->GetAngle();
		float radians = float(fAngle * (M_PI / 180.0f));

		float fTargetY = vPos.y + (vObjPos.x - vPos.x) * tan(radians);


		if (vObjPos.y > fTargetY)
		{
			_OtherObj->SetPos(Vec2(vObjPos.x, fTargetY));
			pOtherMovement->SetGround(true);
		}
	}


	

	//float up = (_OwnCol->GetScale().y / 2.f + _OtherCol->GetScale().y / 2.f - abs(_OwnCol->GetPos().y - _OtherCol->GetPos().y)) / 2.f;
	//_OtherObj->SetPos(Vec2(_OtherObj->GetPos().x, _OtherObj->GetPos().y - up));
}