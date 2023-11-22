#include "pch.h"
#include "CPlatform.h"

#include "components.h"

#include "CPenitent.h"

CPlatform::CPlatform()
	: m_pCollider(nullptr)
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
	if (_OtherCol->GetName() == L"Penitent_HitBox" || _OtherObj->GetName() == L"Pope" || _OtherObj->GetLayerIdx() == (UINT)LAYER::PROJECTILE || _OtherObj->GetName() == L"GiantSword")
		return;

	CPenitent* pPenitent = dynamic_cast<CPenitent*>(_OtherObj);
	if (pPenitent)
	{
		UINT CurState = pPenitent->GetComponent<CStateMachine>()->GetCurState();

		if (CurState == (UINT)PENITENT_STATE::LADDER || CurState == (UINT)PENITENT_STATE::LADDERUP || CurState == (UINT)PENITENT_STATE::LADDERDOWN)
			return;
	}

	Vec2 vPos = _OwnCol->GetPos();
	Vec2 vScale = _OwnCol->GetScale();
	Vec2 vObjPos = _OtherObj->GetPos();
	CMovement* pOtherMovement = _OtherObj->GetComponent<CMovement>();

	float fAngle = m_pCollider->GetAngle();
	float radians = float(fAngle * (M_PI / 180.0f));

	float fTargetY = vPos.y + (vObjPos.x - vPos.x) * tan(radians);

	if (m_pCollider->GetAngle() == 0.f)
	{
		if (vObjPos.y > fTargetY && vPos.y + vScale.y/2.f > vObjPos.y)
		{
			if(pOtherMovement->GetVelocity().y >= 0)
			{
				CPenitent* pPenitent = dynamic_cast<CPenitent*>(_OtherObj);
				if (pPenitent != nullptr && pPenitent->GetDownPlatform())
				{
					return;
				}

				_OtherObj->SetPos(Vec2(vObjPos.x, fTargetY));
				pOtherMovement->SetGround(true);
			}
		}
	}
	else
	{
		if (vObjPos.y > fTargetY && pOtherMovement->GetVelocity().y >= 0)
		{
			_OtherObj->SetPos(Vec2(vObjPos.x, fTargetY));
			pOtherMovement->SetGround(true);
		}
	}


	//Vec2 vPos = _OwnCol->GetPos();
	//Vec2 vScale = _OwnCol->GetScale();
	//Vec2 vObjPos = _OtherObj->GetPos();


	// 몬스터가 땅의 끝까지 왔는지 체크
	if (abs(vPos.x - vObjPos.x) >= abs(vScale.x / 2.f - _OtherCol->GetScale().x / 2.f))
	{
		_OtherObj->SetPlatEnd(true);
	}
	else
	{
		_OtherObj->SetPlatEnd(false);
	}


}