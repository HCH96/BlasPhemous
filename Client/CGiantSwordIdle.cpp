#include "pch.h"
#include "CGiantSwordIdle.h"

#include "CPenitent.h"
#include "CLevelMgr.h"


CGiantSwordIdle::CGiantSwordIdle()
	: m_pTarget(nullptr)
	, m_vVelocity(Vec2(0.f,0.f))
{
}

CGiantSwordIdle::~CGiantSwordIdle()
{
}

void CGiantSwordIdle::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;

	Vec2 vPos = pOwner->GetPos();
	Vec2 TargetPos = m_pTarget->GetPos();
	float fAngle = pOwner->GetAngle();

	// Player�� �����ʿ� �ִ� ���
	if (m_pTarget->GetPos().x - pOwner->GetPos().x > 0)
	{
		TargetPos += Vec2(-200.f, -200.f);
		fAngle += 30.f * _DT;
	}
	// ���ʿ� �ִ� ���
	else
	{
		TargetPos += Vec2(200.f, -200.f);
		fAngle += -30.f * _DT;
	}


	// �̵��� ����� �ӵ��� ���ѵ� �ڽ��� ��ġ�� ����
	Vec2 vDir = TargetPos - vPos;

	// Player�� �����ʿ� �ִ� ���
	if (m_pTarget->GetPos().x - pOwner->GetPos().x > 0)
	{
		if (m_vVelocity.x < 0)
		{
			m_vVelocity += vDir.Normalize() * 10.f;
		}
		else
		{
			m_vVelocity += vDir.Normalize() * 3.f;
		}

	}
	// ���ʿ� �ִ� ���
	else
	{
		if (m_vVelocity.x > 0)
		{
			m_vVelocity += vDir.Normalize() * 10.f;
		}
		else
		{
			m_vVelocity += vDir.Normalize() * 3.f;
		}
	}

	// �ִ� �ӵ� ����
	if (m_vVelocity.Length() > 200.f)
	{
		m_vVelocity = m_vVelocity.Normalize() * 200.f;
	}

	// ��ġ ����
	vPos = vPos + m_vVelocity * _DT;
	pOwner->SetPos(vPos);

	// ���� ����
	if (fabs(fAngle) > 30.f)
	{
		if (fAngle > 0.f)
		{
			fAngle = 30.f;
		}
		else
		{
			fAngle = -30.f;
		}
	}

	pOwner->SetAngle(fAngle);


	// ���� ��ġ�� ����
	CAnimator* pEye = pOwner->GetComponent<CAnimator>(L"GiantSwordEye");

	Vec2 vEyeDir = m_pTarget->GetPos() - pOwner->GetPos();
	vEyeDir.Normalize();
	vEyeDir.Rotate(-fAngle);


	vEyeDir = vEyeDir * 3.f;

	pEye->FixAnimOffset(L"Idle", vEyeDir);
}

void CGiantSwordIdle::Enter()
{
	CObj* pOwner = GetOwnerObj;
	CAnimator* pAnimator = pOwner->GetComponent<CAnimator>();
	CAnimator* pEye = pOwner->GetComponent<CAnimator>(L"GiantSwordEye");
	CCollider* pCollider = pOwner->GetComponent<CCollider>();

	m_pTarget = CLevelMgr::GetInst()->GetPenitent();

	pCollider->SetTime(-1.f);
	pCollider->On();



	pAnimator->Play(L"Idle", true);
	pEye->Play(L"Idle", true);

}

void CGiantSwordIdle::Exit()
{
}

