#include "pch.h"
#include "CElderBrotherIntroJump.h"

CElderBrotherIntroJump::CElderBrotherIntroJump()
{
}

CElderBrotherIntroJump::~CElderBrotherIntroJump()
{
}

void CElderBrotherIntroJump::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	CMovement* pMovement = pOwner->GetComponent<CMovement>();

	int iCurFrame = pAnimator->GetCurFrame();

	if (iCurFrame > 18 && !pMovement->IsGround())
	{
		pAnimator->SetFrame(18);
	}

	if (m_PrevFrame == 18 && pMovement->IsGround())
	{
		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"ELDER_BROTHER_LANDING", L"sound\\Object\\Monster\\Boss\\ElderBrother\\ELDER_BROTHER_LANDING.wav");
		pSound->Play();

		pAnimator->SetFrame(19);
	}

	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)ELDERBROTHER::IDLE);
	}


	m_PrevFrame = iCurFrame;


}

void CElderBrotherIntroJump::Enter()
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	CMovement* pMovement = pOwner->GetComponent<CMovement>();

	pMovement->SetVelocity(Vec2(0.f, 1000.f));
	bool bDir = pOwner->GetDir();

	if (bDir)
	{
		pAnimator->Play(L"Jump", false);
	}
	else
	{
		pAnimator->Play(L"Jump_L", false);
	}

	pAnimator->SetFrame(9);

	m_PrevFrame = 0;

}

void CElderBrotherIntroJump::Exit()
{
}

