#include "pch.h"
#include "CElderBrotherAttack.h"

#include "CLevelMgr.h"
#include "CObj.h"

#include "CLevel.h"

#include "CSpawner.h"

CElderBrotherAttack::CElderBrotherAttack()
	: m_pTarget(nullptr)
	, m_PrevFrame(0)
{
}

CElderBrotherAttack::~CElderBrotherAttack()
{
}


void CElderBrotherAttack::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
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


		if (pOwner->GetDir())
		{
			m_pSpawner->On(pOwner->GetPos()+10.f, pOwner->GetDir());
		}
		else
		{
			m_pSpawner->On(pOwner->GetPos() - 10.f, pOwner->GetDir());
		}
	}



	if (m_PrevFrame == 14 && iCurFrame == 15)
	{
		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"ELDER_BROTHER_CORPSE_WAVE", L"sound\\Object\\Monster\\Boss\\ElderBrother\\ELDER_BROTHER_CORPSE_WAVE.wav");
		pSound->SetVolume(50.f);
		pSound->Play();
		
		pSound = CAssetMgr::GetInst()->LoadSound(L"ELDER_BROTHER_ATTACK_VOICE", L"sound\\Object\\Monster\\Boss\\ElderBrother\\ELDER_BROTHER_ATTACK_VOICE.wav");
		pSound->Play();

		pSound = CAssetMgr::GetInst()->LoadSound(L"ELDER_BROTHER_ATTACK_HIT", L"sound\\Object\\Monster\\Boss\\ElderBrother\\ELDER_BROTHER_ATTACK_HIT.wav");
		pSound->Play();

		CCamera::GetInst()->Shake(0.3f, 0.8f);
	}

	if (m_PrevFrame == 17 && iCurFrame == 18)
	{
		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"ELDER_BROTHER_CORPSE_WAVE_2", L"sound\\Object\\Monster\\Boss\\ElderBrother\\ELDER_BROTHER_CORPSE_WAVE_2.wav");
		pSound->SetVolume(50.f);
		pSound->Play();
	}

	if (m_PrevFrame == 19 && iCurFrame == 20)
	{
		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"ELDER_BROTHER_CORPSE_WAVE_3", L"sound\\Object\\Monster\\Boss\\ElderBrother\\ELDER_BROTHER_CORPSE_WAVE_3.wav");
		pSound->SetVolume(50.f);
		pSound->Play();
	}

	m_PrevFrame = iCurFrame;


	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)ELDERBROTHER::IDLE);
	}

}

void CElderBrotherAttack::Enter()
{

	// Spawner 가져오기
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	const vector<CObj*> pLayer = pCurLevel->GetObjects(LAYER::SPAWNER);
	m_pSpawner = dynamic_cast<CSpawner*>(pLayer[0]);


	m_pTarget = CLevelMgr::GetInst()->GetPenitent();
	CObj* pOwner = GetOwnerObj;
	
	Vec2 vTargetPos = m_pTarget->GetPos();
	Vec2 vPos = pOwner->GetPos();

	// 방향 정하기
	if ((vTargetPos.x - vPos.x) > 0)
	{
		pOwner->SetDir(true);
	}
	else
	{
		pOwner->SetDir(false);
	}

	CCollider* pCollider = pOwner->GetComponent<CCollider>();
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	bool bDir = pOwner->GetDir();
	//pCollider->SetTime(0.f);

	if (bDir)
	{
		pAnimator->Play(L"Attack", false);
	}
	else
	{
		pAnimator->Play(L"Attack_L", false);
	}

	m_PrevFrame = 0;

}

void CElderBrotherAttack::Exit()
{
	CObj* pOwner = GetOwnerObj;
	CCollider* pCollider = pOwner->GetComponent<CCollider>();
	//pCollider->SetTime(-1.f);
	pCollider->On();
}

