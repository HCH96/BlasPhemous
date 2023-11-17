#include "pch.h"
#include "CElderBrotherJump.h"

#include "CLevelMgr.h"

CElderBrotherJump::CElderBrotherJump()
	: m_pTarget(nullptr)
	, m_fStart(0.f)
	, m_fEnd(0.f)
	, m_fAcc(0.f)
	, m_fDuration(0.80f)
	, m_PrevFrame(0)
{
}

CElderBrotherJump::~CElderBrotherJump()
{
}



void CElderBrotherJump::finaltick(float _DT)
{
	// 0~ 8frame 도약 준비 / 9 ~ 17 도약 / 18 하강 / 19~ 27 Frame 착지

	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	CMovement* pMovement = pOwner->GetComponent<CMovement>();
	Vec2 vCurPos = pOwner->GetPos();

	int iCurFrame = pAnimator->GetCurFrame();

	// x축 값 이동
	if(iCurFrame > 8 && iCurFrame < 19)
	{
		m_fAcc += _DT;
		if (m_fAcc > m_fDuration)
		{
			m_fAcc = m_fDuration;
		}

	}

	float fCurX = m_fStart + m_fAcc/ m_fDuration * (m_fEnd - m_fStart);

	// Jump 
	if (m_PrevFrame == 8 && iCurFrame == 9)
	{
		pMovement->SetGround(false);
		pMovement->SetVelocity(Vec2(pMovement->GetVelocity().x, pMovement->GetJumpVel()));
	}

	Vec2 vVel = pMovement->GetVelocity();



	pOwner->SetPos(Vec2(fCurX, vCurPos.y));



	//float fCurX = vCurPos.x;
	//fCurX = lerp(fCurX, m_fLandingPos, 0.04f);
	//pOwner->SetPos(Vec2(fCurX, vCurPos.y));


	m_PrevFrame = iCurFrame;

	if (pAnimator->IsFinish())
	{
		GetOwnerSM()->ChangeState((UINT)ELDERBROTHER::ATTACK);
	}
}

void CElderBrotherJump::Enter()
{
	//Player의 속도를 이용해 착지지점 알아내기
	m_pTarget = CLevelMgr::GetInst()->GetPenitent();
	CMovement* pTargetMovement = m_pTarget->GetComponent<CMovement>();
	Vec2 vTargetVel = pTargetMovement->GetVelocity();


	// 선형 보간을 위한 x 좌표 세팅 
	CObj* pOwner = GetOwnerObj;

	m_fStart = pOwner->GetPos().x;
	m_fEnd = m_pTarget->GetPos().x + vTargetVel.x * 0.8f;

	
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

}

void CElderBrotherJump::Exit()
{
	m_fAcc = 0.f;
	m_PrevFrame = 0;
}
