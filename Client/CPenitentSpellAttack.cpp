#include "pch.h"
#include "CPenitentSpellAttack.h"


CPenitentSpellAttack::CPenitentSpellAttack()
{
}

CPenitentSpellAttack::~CPenitentSpellAttack()
{
}


void CPenitentSpellAttack::finaltick(float _DT)
{
	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CAnimator* pEffector = GetOwnerObj->GetComponent<CAnimator>(L"Penitent_Effector");

	CCollider* pHitBox = GetOwnerObj->GetComponent<CCollider>(L"Penitent_HitBox");

	int iCurFrame = pEffector->GetCurFrame();

	if (iCurFrame == 46 && m_iPrevFrame == 45)
	{
		pHitBox->On();
	}

	if (iCurFrame == 50 && m_iPrevFrame == 49)
	{
		pHitBox->On();
	}

	if (iCurFrame == 54 && m_iPrevFrame == 53)
	{
		pHitBox->On();
	}




	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)PENITENT_STATE::IDLE);
	}

	m_iPrevFrame = iCurFrame;
}

void CPenitentSpellAttack::Enter()
{
	CPenitent* pPenitent = dynamic_cast<CPenitent*>(GetOwnerObj);

	pPenitent->SetMP(pPenitent->GetMP() - 1);

	CAnimator* pAnimator = GetOwnerObj->GetComponent<CAnimator>();
	CAnimator* pEffector = GetOwnerObj->GetComponent<CAnimator>(L"Penitent_Effector");
	CCollider* pHitBox = GetOwnerObj->GetComponent<CCollider>(L"Penitent_HitBox");

	pHitBox->SetScale(Vec2(400.f, 700.f));
	pHitBox->SetOffsetPos(Vec2(0.f, -350.f));
	pHitBox->SetTime(0.05f);


	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"PENITENT_ACTIVATE_PRAYER", L"sound\\Object\\Player\\PENITENT_ACTIVATE_PRAYER.wav");
	pSound->Play();

	int iDir = GetOwnerObj->GetDir();

	if (iDir)
	{
		pAnimator->Play(L"SpellAttack", true);
		pEffector->Play(L"SpellAttack", false);
	}
	else
	{
		pAnimator->Play(L"SpellAttack_L", true);
		pEffector->Play(L"SpellAttack_L", false);
	}

	m_iPrevFrame = 0;

}

void CPenitentSpellAttack::Exit()
{
}
