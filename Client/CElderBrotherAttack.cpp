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


	if (m_PrevFrame == 13 && iCurFrame == 14)
	{
		if (pOwner->GetDir())
		{
			m_pSpawner->On(pOwner->GetPos()+10.f, pOwner->GetDir());

		}
		else
		{
			m_pSpawner->On(pOwner->GetPos() - 10.f, pOwner->GetDir());
		}

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

}

void CElderBrotherAttack::Exit()
{
	CObj* pOwner = GetOwnerObj;
	CCollider* pCollider = pOwner->GetComponent<CCollider>();
	//pCollider->SetTime(-1.f);
	pCollider->On();
}

