#include "pch.h"
#include "CElderBrotherJump.h"

#include "CCamera.h"

#include "CLevelMgr.h"

CElderBrotherJump::CElderBrotherJump()
	: m_pTarget(nullptr)
	, m_fStart(0.f)
	, m_fEnd(0.f)
	, m_fAcc(0.f)
	, m_fDuration(0.80f)
	, m_PrevFrame(0)
	, m_fJumpStart(0.f)
	, m_fJumpEnd(0.f)
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

	// 플레이어 예상 위치 찾기
	if (m_PrevFrame == 7 && iCurFrame == 8)
	{
		CMovement* pTargetMovement = m_pTarget->GetComponent<CMovement>();
		Vec2 vTargetVel = pTargetMovement->GetVelocity();

		m_fStart = pOwner->GetPos().x;
		m_fEnd = m_pTarget->GetPos().x + vTargetVel.x * 1.2f;
	}

	// x축 값 이동
	if(iCurFrame > 8 && iCurFrame < 19)
	{
		m_fAcc += _DT;
		if (m_fAcc > m_fDuration)
		{
			m_fAcc = m_fDuration;
		}
	}

	if (m_PrevFrame == 18 && iCurFrame == 19)
	{

		CCamera::GetInst()->Shake(0.3f, 0.8f);
	}

	float fCurX = m_fStart + m_fAcc/ m_fDuration * (m_fEnd - m_fStart);


	// y 축 값 이동
	
	// Jump 중간 시간
	float mid = 0.36f;

	// 중간 시간에서 부터의 시간
	float t = abs(mid - m_fAcc) / m_fDuration / 2.f;

	float fCurY = vCurPos.y;

	// 올라갈 때 가중치가 작아져야 함
	if (m_fAcc < mid && m_fAcc>0.f)
	{
		fCurY = lerp(fCurY, m_fJumpEnd, 0.1f);
	}

	// 내려올 때 가중치가 커져야 함
	if (m_fAcc < m_fDuration - 0.08f && m_fAcc >mid)
	{
		float weightedT = t * t * (0.5f - 0.25f * t);
		fCurY = lerp(fCurY, m_fJumpStart + 50.f, weightedT);
	}



	// Jump 
	if (m_PrevFrame == 8 && iCurFrame == 9)
	{
		pMovement->SetGround(false);

		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"ELDER_BROTHER_JUMP_VOICE", L"sound\\Object\\Monster\\Boss\\ElderBrother\\ELDER_BROTHER_JUMP_VOICE.wav");
		pSound->Play();


		pSound = CAssetMgr::GetInst()->LoadSound(L"ELDER_BROTHER_JUMP", L"sound\\Object\\Monster\\Boss\\ElderBrother\\ELDER_BROTHER_JUMP.wav");
		pSound->Play();

		//pMovement->SetVelocity(Vec2(pMovement->GetVelocity().x, pMovement->GetJumpVel()));
	}

	if (m_PrevFrame == 17 && iCurFrame == 18)
	{
		Vec2 vTargetPos = m_pTarget->GetPos();

		// 방향 정하기
		if ((vTargetPos.x - vCurPos.x) > 0)
		{
			pOwner->SetDir(true);
			pAnimator->PlayFromFrame(L"Jump", 18, false);
		}
		else
		{
			pOwner->SetDir(false);
			pAnimator->PlayFromFrame(L"Jump_L", 18, true);
		}
	}

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



	//Vec2 vVel = pMovement->GetVelocity();



	pOwner->SetPos(Vec2(fCurX, fCurY));



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
	m_fEnd = m_pTarget->GetPos().x + vTargetVel.x * 1.2f;

	// y축 좌표 세팅
	m_fJumpStart = pOwner->GetPos().y;
	m_fJumpEnd = pOwner->GetPos().y - 700.f;


	
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
