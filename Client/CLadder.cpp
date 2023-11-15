#include "pch.h"
#include "CLadder.h"

#include "CKeyMgr.h"

#include "CPenitent.h"

CLadder::CLadder()
	: m_pCollider(nullptr)
{
	m_pCollider = AddComponent<CCollider>(L"Ladder");
	m_pCollider->SetOffsetPos(Vec2(0.f, 0.f));
}

CLadder::CLadder(const CLadder& _Origin)
	: CObj(_Origin)
	, m_pCollider(nullptr)
{
	m_pCollider = GetComponent<CCollider>();
}
CLadder::~CLadder()
{
}

void CLadder::begin()
{
	m_pCollider->SetScale(GetScale());
}

void CLadder::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if (_OtherCol->GetName() == L"Penitent_HitBox")
		return;

	Vec2 vPos = _OwnCol->GetPos();
	CPenitent* pPenitent = dynamic_cast<CPenitent*>(_OtherObj);
	CStateMachine* pSM = pPenitent->GetComponent<CStateMachine>();



	if (KEY_PRESSED(KEY::DOWN) && vPos.y - _OwnCol->GetScale().y/ 2.f >= _OtherObj->GetPos().y)
	{
		_OtherObj->SetPos(Vec2(vPos.x, _OtherObj->GetPos().y));
		pSM->ChangeState((UINT)PENITENT_STATE::LADDERDOWN);

	}
	else if (KEY_PRESSED(KEY::UP) && vPos.y - _OwnCol->GetScale().y / 2.f + 10.f >= _OtherObj->GetPos().y)
	{
	}
	else if (KEY_PRESSED(KEY::UP) || KEY_PRESSED(KEY::DOWN))
	{
		_OtherObj->SetPos(Vec2(vPos.x, _OtherObj->GetPos().y));
		pSM->ChangeState((UINT)PENITENT_STATE::LADDER);
	}

}

void CLadder::EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if (_OtherCol->GetName() == L"Penitent_HitBox")
		return;

	Vec2 vPos = _OwnCol->GetPos();
	CPenitent* pPenitent = dynamic_cast<CPenitent*>(_OtherObj);
	CStateMachine* pSM = pPenitent->GetComponent<CStateMachine>();
	UINT iCurState = pSM->GetCurState();


	if (vPos.y - _OwnCol->GetScale().y / 2.f >= _OtherObj->GetPos().y && iCurState == (UINT)PENITENT_STATE::LADDER)
	{
		pSM->ChangeState((UINT)PENITENT_STATE::IDLE);
	}

	if (vPos.y + _OwnCol->GetScale().y / 2.f <= _OtherObj->GetPos().y && iCurState == (UINT)PENITENT_STATE::LADDER)
	{
		pSM->ChangeState((UINT)PENITENT_STATE::FALL);
	}


}

