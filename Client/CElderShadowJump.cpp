#include "pch.h"
#include "CElderShadowJump.h"

#include "CLevelMgr.h"
#include "CLevel.h"

CElderShadowJump::CElderShadowJump()
{
}

CElderShadowJump::~CElderShadowJump()
{
}

void CElderShadowJump::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	int iCurFrame = pAnimator->GetCurFrame();


	if (m_PrevFrame == 8 && iCurFrame == 9)
	{
		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"ELDER_BROTHER_JUMP_VOICE", L"sound\\Object\\Monster\\Boss\\ElderBrother\\ELDER_BROTHER_JUMP_VOICE.wav");
		pSound->SetVolume(100.f);
		pSound->Play();


		pSound = CAssetMgr::GetInst()->LoadSound(L"ELDER_BROTHER_JUMP", L"sound\\Object\\Monster\\Boss\\ElderBrother\\ELDER_BROTHER_JUMP.wav");
		pSound->SetVolume(100.f);
		pSound->Play();
	}

	if (iCurFrame >= 9)
	{
		Vec2 vPos = pOwner->GetPos();
		vPos.y -= 1000.f * _DT;
		pOwner->SetPos(vPos);
	}



	if (pAnimator->IsFinish())
	{
		CLevelMgr::GetInst()->GetCurLevel()->IntroEnd();
		pOwner->Destroy();
	}

	m_PrevFrame = iCurFrame;
}

void CElderShadowJump::Enter()
{
	CObj* pOwner = GetOwnerObj;
	Vec2 vPos = pOwner->GetPos();

	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	bool bDir = pOwner->GetDir();

	if (bDir)
	{
		pAnimator->Play(L"Jump", false);
	}
	else
	{
		pAnimator->Play(L"Jump_L", false);
	}

	m_PrevFrame = 0;

}

void CElderShadowJump::Exit()
{
}

