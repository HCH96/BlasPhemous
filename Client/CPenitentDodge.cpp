#include "pch.h"
#include "CPenitentDodge.h"

CPenitentDodge::CPenitentDodge()
	: m_iCurFrame(0)
	, m_iDir(true)
{
}

CPenitentDodge::~CPenitentDodge()
{
}

void CPenitentDodge::finaltick(float _DT)
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	m_iCurFrame = pAnimator->GetCurFrame();

	// 속도 변화
	if (m_iCurFrame < 3 && m_iCurFrame > 0)
	{
		if (m_iDir)
		{
			pMovement->SetVelocity(Vec2(1050.f, pMovement->GetVelocity().y));
		}
		else
		{
			pMovement->SetVelocity(Vec2(-1050.f, pMovement->GetVelocity().y));
		}
	}

	if (m_iCurFrame == 11)
	{
		if (m_iDir && KEY_PRESSED(KEY::RIGHT) && KEY_NONE(KEY::LEFT))
			GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::DODGETORUN);

		if (!m_iDir && KEY_PRESSED(KEY::LEFT) && KEY_NONE(KEY::RIGHT))
			GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::DODGETORUN);
	}


	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::IDLE);
	}

	
	if (!pMovement->IsGround())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::FALLFORWARD);
	}

	if (KEY_TAP(KEY::F) || KEY_PRESSED(KEY::F))
	{
		pMovement->SetGround(false);
		pMovement->SetVelocity(Vec2(pMovement->GetVelocity().x, pMovement->GetJumpVel()));
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::JUMPFORWARD);
	}


}

void CPenitentDodge::Enter()
{
	CCamera::GetInst()->SetLookAtOffsetX(20.f);
	CAnimator* pDustAnimator = GetOwnerObj->GetComponent<CAnimator>(L"Dust_Animator");
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	CCollider* pCol = GetOwnerObj->GetComponent<CCollider>();
	pCol->SetScale(Vec2(60.f, 70.f));
	pCol->SetOffsetPos(Vec2(0.f, -35.f));

	m_iCurFrame = 0;
	m_iDir = GetOwnerObj->GetDir();

	pMovement->SetMaxSpeed(800.f);
	pMovement->SetGravity(Vec2(0.f, 8000.f));

	pDustAnimator->SetLock(true);
	pDustAnimator->SetTmpPos(GetOwnerObj->GetPos());



	if (m_iDir)
	{
		pDustAnimator->Play(L"StartDodge", false);
		pAnimator->Play(L"Dodge", false);
		pMovement->SetVelocity(Vec2(2.f, 0.f) * pMovement->GetInitSpeed());
	}
	else
	{
		pDustAnimator->Play(L"StartDodge_L", false);
		pAnimator->Play(L"Dodge_L", false);
		pMovement->SetVelocity(Vec2(-2.f, 0.f) * pMovement->GetInitSpeed());
	}
}

void CPenitentDodge::Exit()
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CMovement* pMovement = GetOwnerObj->GetComponent<CMovement>();
	bool bDir = GetOwnerObj->GetDir();

	// Movement 설정 값 되돌려주기
	pMovement->SetMaxSpeed(300.f);
	pMovement->SetGravity(Vec2(0.f, 2000.f));
	pMovement->SetMaxSpeed(400.f);

	CCollider* pCol = GetOwnerObj->GetComponent<CCollider>();
	pCol->SetScale(Vec2(40.f, 100.f));
	pCol->SetOffsetPos(Vec2(0.f, -50.f));

	CAnimator* pDustAnimator = GetOwnerObj->GetComponent<CAnimator>(L"Dust_Animator");
	//pDustAnimator->SetLock(false);

}



