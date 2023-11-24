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

		if (fCurAcc > 0.02)
		{
			++iCurFrm;
			fCurAcc -= fDuration;

			++m_iCount;

			if (m_iCount > 2)
			{
				CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"PENITENT_CLIMB_LADDER_2", L"sound\\Object\\Player\\PENITENT_CLIMB_LADDER_2.wav");
				pSound->Play();
				m_iCount = 0;
			}


		}
		pObj->SetPos(Vec2(pObj->GetPos().x, pObj->GetPos().y + 200.f * _DT));
	}

	if (KEY_PRESSED(KEY::UP))
	{
		fCurAcc += _DT;

		if (fCurAcc > 0.02)
		{
			--iCurFrm;
			fCurAcc -= fDuration;

			++m_iCount;

			if (m_iCount > 2)
			{
				CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"PENITENT_CLIMB_LADDER_2", L"sound\\Object\\Player\\PENITENT_CLIMB_LADDER_2.wav");
				pSound->Play();
				m_iCount = 0;
			}
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

	m_iCount = 0;

	pAnimator->Play(L"Ladder", true);

}

void CPenitentLadder::Exit()
{
	CObj* pObj = GetOwnerObj;
	CMovement* pMovement = pObj->GetComponent<CMovement>();
	pMovement->UseGravity(true);
}

