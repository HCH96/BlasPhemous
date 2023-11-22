#include "pch.h"
#include "CGiantSwordIdle.h"

#include "CPenitent.h"
#include "CLevelMgr.h"
#include "CGiantSword.h"

#include "CKeyMgr.h"


CGiantSwordIdle::CGiantSwordIdle()
	: m_pTarget(nullptr)
	, m_vVelocity(Vec2(0.f,0.f))
	, m_bSpinReady(false)
{
}

CGiantSwordIdle::~CGiantSwordIdle()
{
}

void CGiantSwordIdle::finaltick(float _DT)
{
	CObj* pOwner = GetOwnerObj;
	CGiantSword* pSword = dynamic_cast<CGiantSword*>(pOwner);


	Vec2 vPos = pOwner->GetPos();
	Vec2 TargetPos = m_pTarget->GetPos();
	float fAngle = pOwner->GetAngle();

	if (pSword->GetHP()<0.f)
	{
		if (fAngle < 1.f && fAngle > -1.f)
		{
			GetOwnerSM()->ChangeState((UINT)GIANTSWORD::VANISH);
		}
		else
		{
			if (fAngle > 0.f)
			{
				fAngle = fAngle - 70.f * _DT;
			}
			else
			{
				fAngle = fAngle + 70.f * _DT;
			}

			pOwner->SetAngle(fAngle);

		}
		return;

	}


	// SpinReady
	if (m_bSpinReady)
	{
		// Player�� �����ʿ� �ִ� ���
		if (m_pTarget->GetPos().x - pOwner->GetPos().x > 0)
		{
			fAngle += 80.f * _DT;
		}
		// ���ʿ� �ִ� ���
		else
		{
			fAngle += -80.f * _DT;
		}

		pOwner->SetAngle(fAngle);

		if (fabs(fAngle) > 90.f)
		{
			m_bSpinReady = false;
			GetOwnerSM()->ChangeState((UINT)GIANTSWORD::SPINATTACK);
		}


		return;
	}


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

	if (fAngle > 180.f)
	{
		fAngle = fAngle - 360.f;
	}

	if (fAngle < -180.f)
	{
		fAngle = fAngle + 360.f;
	}

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


	if (KEY_TAP(KEY::K))
	{
		m_bSpinReady = true;
	}

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

