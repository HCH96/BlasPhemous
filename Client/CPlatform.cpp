#include "pch.h"
#include "CPlatform.h"

#include "components.h"


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
	float fAngle = m_pCollider->GetAngle();
	float radians = fAngle * (M_PI / 180.0f);

	Vec2 vPos = _OwnCol->GetPos();
	Vec2 vObjPos = _OtherObj->GetPos();

	float fTargetY = vPos.y + (vObjPos.x - vPos.x) * tan(radians);


	
	
	
	if (vObjPos.y > fTargetY)
	{
		_OtherObj->SetPos(Vec2(vObjPos.x, fTargetY));
	}

	//float up = (_OwnCol->GetScale().y / 2.f + _OtherCol->GetScale().y / 2.f - abs(_OwnCol->GetPos().y - _OtherCol->GetPos().y)) / 2.f;
	//_OtherObj->SetPos(Vec2(_OtherObj->GetPos().x, _OtherObj->GetPos().y - up));
}