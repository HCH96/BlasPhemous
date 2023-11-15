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
	if (_OtherCol->GetName() == L"Penitent_HitBox")
		return;

	CPenitent* pPenitent = dynamic_cast<CPenitent*>(_OtherObj);
	if (pPenitent)
	{
		UINT CurState = pPenitent->GetComponent<CStateMachine>()->GetCurState();

		if (CurState == (UINT)PENITENT_STATE::LADDER || CurState == (UINT)PENITENT_STATE::LADDER || CurState == (UINT)PENITENT_STATE::LADDERDOWN)
			return;
	}



	Vec2 vPos = _OwnCol->GetPos();
	Vec2 vScale = _OwnCol->GetScale();
	Vec2 vObjPos = _OtherObj->GetPos();
	CMovement* pOtherMovement = _OtherObj->GetComponent<CMovement>();

	float fAngle = m_pCollider->GetAngle();
	float radians = float(fAngle * (M_PI / 180.0f));

	float fTargetY = vPos.y + (vObjPos.x - vPos.x) * tan(radians);

	//// 오른쪽으로 충돌했을 경우
	//if (vPos.x + vScale.x / 2.f < vObjPos.x && (pOtherMovement->GetVelocity().x < 0) && _OtherObj->GetLayerIdx() == (UINT)LAYER::PLAYER)
	//{

	//	CStateMachine* pSM = _OtherObj->GetComponent<CStateMachine>();

	//	_OtherObj->SetPos(Vec2(vObjPos.x, fTargetY));
	//	pSM->ChangeState((UINT)PENITENT_STATE::CLIMB);
	//	pOtherMovement->SetGround(true);


	//	//_OtherObj->SetPos(Vec2(vPos.x + _OwnCol->GetScale().x / 2.f + _OtherCol->GetScale().x/2.f, vObjPos.y));
	//}
	//// 왼쪽으로 충돌했을 경우
	//else if (vPos.x - vScale.x / 2.f > vObjPos.x && (pOtherMovement->GetVelocity().x > 0))
	//{
	//	CStateMachine* pSM = _OtherObj->GetComponent<CStateMachine>();

	//	pSM->ChangeState((UINT)PENITENT_STATE::CLIMB);
	//	_OtherObj->SetPos(Vec2(vObjPos.x, fTargetY));
	//	pOtherMovement->SetGround(true);

	//	//_OtherObj->SetPos(Vec2(vPos.x - _OwnCol->GetScale().x / 2.f - _OtherCol->GetScale().x / 2.f, vObjPos.y));
	//}

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


}