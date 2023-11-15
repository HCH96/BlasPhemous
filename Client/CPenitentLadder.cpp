#include "pch.h"
#include "CPenitentLadder.h"

#include "CAnim.h"

CPenitentLadder::CPenitentLadder()
{
}

CPenitentLadder::~CPenitentLadder()
{
}

void CPenitentLadder::finaltick(float _DT)
{
	CObj* pObj = GetOwnerObj;
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	CAnimator* pAnimator = pObj->GetComponent<CAnimator>();
	CAnim* pCurAnim = pAnimator->GetCurAnimp();

	int iCurFrm = pAnimator->GetCurFrame();
	float fCurAcc = pCurAnim->GetAcc() - _DT;
	float fDuration = pCurAnim->GetDuration();

	if (KEY_PRESSED(KEY::DOWN))
	{
		fCurAcc += _DT;

		if (fCurAcc > fDuration)
		{
			++iCurFrm;
			fCurAcc -= fDuration;
		}
		pObj->SetPos(Vec2(pObj->GetPos().x, pObj->GetPos().y + 200.f * _DT));
	}

	if (KEY_PRESSED(KEY::UP))
	{
		fCurAcc += _DT;

		if (fCurAcc > fDuration)
		{
			++iCurFrm;
			fCurAcc -= fDuration;
		}

		pObj->SetPos(Vec2(pObj->GetPos().x, pObj->GetPos().y - 200.f * _DT));
	}

	if (iCurFrm < 0)
	{
		iCurFrm = pCurAnim->GetMaxFrm() -1;
	}

	if (iCurFrm >= pCurAnim->GetMaxFrm())
	{
		iCurFrm = 0;
	}
	pCurAnim->SetFrame(iCurFrm);
	pCurAnim->SetAcc(fCurAcc);

	if (KEY_TAP(KEY::F))
	{
		pMovement->SetGround(false);
		pMovement->SetVelocity(Vec2(pMovement->GetVelocity().x, pMovement->GetJumpVel()));
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::JUMP);

		if (KEY_PRESSED(KEY::LEFT) || KEY_PRESSED(KEY::RIGHT))
		{
			GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::JUMPFORWARD);
		}
	}

}

void CPenitentLadder::Enter()
{
	CObj* pObj = GetOwnerObj;
	CAnimator* pAnimator = pObj->GetComponent<CAnimator>();
	CMovement* pMovement = pObj->GetComponent<CMovement>();
	pMovement->SetVelocity(Vec2(0.f, 0.f));
	CStateMachine* pSM = pObj->GetComponent<CStateMachine>();
	pMovement->UseGravity(false);
	int iDir = pObj->GetDir();

	UINT iPrevState = pSM->GetPrevState();
	if (iPrevState == (UINT)PENITENT_STATE::LADDERDOWN)
	{
		Vec2 vPos = pObj->GetPos();
		pObj->SetPos(Vec2(vPos.x, vPos.y+100.f));
	}

	pAnimator->Play(L"Ladder", true);

}

void CPenitentLadder::Exit()
{
	CObj* pObj = GetOwnerObj;
	CMovement* pMovement = pObj->GetComponent<CMovement>();
	pMovement->UseGravity(true);
}

