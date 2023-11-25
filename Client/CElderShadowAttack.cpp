#include "pch.h"
#include "CElderShadowAttack.h"

CElderShadowAttack::CElderShadowAttack()
{
}

CElderShadowAttack::~CElderShadowAttack()
{
}

void CElderShadowAttack::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	bool bDir = pOwner->GetDir();
	int iCurFrame = pAnimator->GetCurFrame();

	if (m_PrevFrame == 11 && iCurFrame == 12)
	{
		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"ELDER_BROTHER_PRE_ATTACK", L"sound\\Object\\Monster\\Boss\\ElderBrother\\ELDER_BROTHER_PRE_ATTACK.wav");
		pSound->Play();
	}


	if (m_PrevFrame == 13 && iCurFrame == 14)
	{
		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"ELDER_BROTHER_ATTACK", L"sound\\Object\\Monster\\Boss\\ElderBrother\\ELDER_BROTHER_ATTACK.wav");
		pSound->Play();

	}

	if (m_PrevFrame == 14 && iCurFrame == 15)
	{
		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"ELDER_BROTHER_ATTACK_VOICE", L"sound\\Object\\Monster\\Boss\\ElderBrother\\ELDER_BROTHER_ATTACK_VOICE.wav");
		pSound->Play();

		pSound = CAssetMgr::GetInst()->LoadSound(L"ELDER_BROTHER_ATTACK_HIT", L"sound\\Object\\Monster\\Boss\\ElderBrother\\ELDER_BROTHER_ATTACK_HIT.wav");
		pSound->Play();

		CCamera::GetInst()->Shake(0.3f, 0.8f);
	}


	if (pAnimator->IsFinish())
	{
		if (m_iCount < 2)
		{
			++m_iCount;

			if (bDir)
			{
				pAnimator->Play(L"Attack", false);
			}
			else
			{
				pAnimator->Play(L"Attack_L", false);
			}
		}
		else
		{
			GetOwnerSM()->ChangeState((UINT)ELDERBROTHER::IDLE);
		}

	}

	m_PrevFrame = iCurFrame;

}

void CElderShadowAttack::Enter()
{
	CObj* pOwner = GetOwnerObj;
	Vec2 vPos = pOwner->GetPos();

	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	bool bDir = pOwner->GetDir();

	if (bDir)
	{
		pAnimator->Play(L"Attack", false);
	}
	else
	{
		pAnimator->Play(L"Attack_L", false);
	}

	m_PrevFrame = 0;
	m_iCount = 0;

}

void CElderShadowAttack::Exit()
{
}


