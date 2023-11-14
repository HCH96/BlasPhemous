#include "pch.h"
#include "CDeathObj.h"

#include "CPenitent.h"

CDeathObj::CDeathObj()
	: m_pCollider(nullptr)
{
	m_pCollider = AddComponent<CCollider>(L"Collider");
	m_pCollider->SetOffsetPos(Vec2(0.f, 0.f));
}

CDeathObj::CDeathObj(const CDeathObj& _Origin)
	: CObj(_Origin)
	, m_pCollider(nullptr)
{
}

CDeathObj::~CDeathObj()
{
}

void CDeathObj::begin()
{
	m_pCollider->SetScale(GetScale());
}

void CDeathObj::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	Vec2 vPos = _OwnCol->GetPos();
	Vec2 vScale = _OwnCol->GetScale();
	Vec2 vObjPos = _OtherObj->GetPos();
	CMovement* pOtherMovement = _OtherObj->GetComponent<CMovement>();

	float fAngle = m_pCollider->GetAngle();
	float radians = float(fAngle * (M_PI / 180.0f));

	float fTargetY = vPos.y + (vObjPos.x - vPos.x) * tan(radians);


	if (vObjPos.y > fTargetY && pOtherMovement->GetVelocity().y >= 0)
	{
		_OtherObj->SetPos(Vec2(vObjPos.x, fTargetY));
		if (_OtherObj->GetLayerIdx() == (UINT)LAYER::PLAYER)
		{
			CPenitent* pPenitent = dynamic_cast<CPenitent*>(_OtherObj);
			CMovement* pMovement = pPenitent->GetComponent<CMovement>();
			pMovement->SetGround(true);
			if (pPenitent->GetState() != (UINT)PENITENT_STATE::DEATH)
			{
				pPenitent->SetState(PENITENT_STATE::DEATH);
			}
		}
	}

	
}


