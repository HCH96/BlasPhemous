#include "pch.h"
#include "CGiantSwordVanish.h"

#include "Pontiff.h"
#include "CGiantSword.h"
#include "Pontiff.h"


CGiantSwordVanish::CGiantSwordVanish()
	: m_fDeadTime(0.f)
{
}

CGiantSwordVanish::~CGiantSwordVanish()
{
}


void CGiantSwordVanish::finaltick(float _DT)
{
	m_fDeadTime += _DT;
	CObj* pOwner = GetOwnerObj;
	CGiantSword* pSword = dynamic_cast<CGiantSword*>(pOwner);
	Pontiff* pPontiff = pSword->GetPontiff();

	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();

	if (pAnimator->IsFinish())
	{
		pAnimator->Stop();
	}

	if (m_fDeadTime > 13.f && pPontiff->GetHP() > 0)
	{
		GetOwnerSM()->ChangeState((UINT)GIANTSWORD::APPEAR);
	}


}

void CGiantSwordVanish::Enter()
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	CAnimator* pEye = pOwner->GetComponent<CAnimator>(L"GiantSwordEye");
	CCollider* pCollider = pOwner->GetComponent<CCollider>();


	CGiantSword* pSword = dynamic_cast<CGiantSword*>(pOwner);
	pSword->SetActive(false);


	pCollider->SetTime(0.f);
	m_fDeadTime = 0.f;



	pAnimator->Play(L"Vanish", false);
	pCollider->SetTime(0.f);
	pEye->Stop();


	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"SWORD_DISAPPEAR", L"sound\\Object\\Monster\\Boss\\Pontiff\\SWORD_DISAPPEAR.wav");
	pSound->Play();
}

void CGiantSwordVanish::Exit()
{
}

