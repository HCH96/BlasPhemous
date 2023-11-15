#include "pch.h"
#include "CLedge.h"

#include "components.h"
#include "CPenitent.h"

CLedge::CLedge()
	: m_pCollider(nullptr)
{
	m_pCollider = AddComponent<CCollider>(L"LedgeCollider");
	m_pCollider->SetOffsetPos(Vec2(0.f, 0.f));
}

CLedge::CLedge(const CLedge& _Origin)
	: CObj(_Origin)
	, m_pCollider(nullptr)
{
	m_pCollider = GetComponent<CCollider>();
}

CLedge::~CLedge()
{
}


void CLedge::begin()
{
	m_pCollider->SetScale(GetScale());
}

void CLedge::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if (_OtherObj->GetName() != L"Penitent")
		return;

	Vec2 vPos = _OwnCol->GetPos();
	Vec2 vScale = _OwnCol->GetScale();
	Vec2 vObjPos = _OtherObj->GetPos();
	CMovement* pOtherMovement = _OtherObj->GetComponent<CMovement>();
	CStateMachine* pSM = _OtherObj->GetComponent<CStateMachine>();
	

	float fAngle = m_pCollider->GetAngle();
	float radians = float(fAngle * (M_PI / 180.0f));
	float fTargetY = vPos.y + (vObjPos.x - vPos.x) * tan(radians); 

	if (vObjPos.y > fTargetY)
	{

		if (vPos.y + vScale.y / 2.f >= vObjPos.y)
		{
			if (pOtherMovement->GetVelocity().y >= 0)
			{
				_OtherObj->SetPos(Vec2(vObjPos.x, fTargetY));
				pOtherMovement->SetGround(true);
			}
		}

		if ((vPos.x + vScale.x / 2.f < vObjPos.x && (pOtherMovement->GetVelocity().x < 0)) || (vPos.x - vScale.x / 2.f > vObjPos.x && (pOtherMovement->GetVelocity().x > 0)))
		{
			if (!pOtherMovement->IsGround())
			{
				_OtherObj->SetPos(Vec2(vObjPos.x, fTargetY + _OtherCol->GetScale().y));
				pSM->ChangeState((UINT)PENITENT_STATE::HANGON);
			}
		}


		if (pOtherMovement->IsGround() && (UINT)PENITENT_STATE::CLIMB == pSM->GetCurState())
		{
			_OtherObj->SetPos(Vec2(vObjPos.x, fTargetY));

		}

		
	}

}

