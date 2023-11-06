#include "pch.h"
#include "CMovement.h"

#include "CObj.h"

CMovement::CMovement(CObj* _Owner)
	: CComponent(_Owner)
	, m_fMass(1.f)
	, m_fInitSpeed(0.f)
	, m_fMaxSpeed(0.f)
	, m_fFrictionScale(0.f)
	, m_bUseGravity(0.f)
	, m_bGround(false)
{
}

CMovement::~CMovement()
{
}

void CMovement::finaltick(float _DT)
{
	CObj* pOwner = GetOwner();

	// 가속도 계산
	m_vAccel = m_vForce / m_fMass;

	// 중력 계산
	if (m_bUseGravity && !m_bGround)
	{
		m_vAccel += m_vGravityForce;
	}

	// 정지에 가까운 상태일 경우 초기속도 주기 (x축 방향만)
	//if (m_vVelocity.x < 0.1f)
	//{
	//	if (!m_vAccel.x != 0)
	//	{
	//		if (pOwner->GetDir())
	//		{
	//			m_vVelocity += Vec2(1.f,0.f) * m_fInitSpeed;
	//		}
	//		else
	//		{
	//			m_vVelocity += Vec2(-1.f, 0.f) * m_fInitSpeed;
	//		}
	//	}
	//}
	//else
	//{
	//	m_vVelocity += m_vAccel * _DT;
	//}

	m_vVelocity += m_vAccel * _DT;

	// 최대 속도 제한
	if (abs(m_vVelocity.x) > m_fMaxSpeed)
	{
		m_vVelocity.x = (m_vVelocity.x / abs(m_vVelocity.x)) * m_fMaxSpeed;
	}

	if (m_vVelocity.y > m_fMaxDown)
	{
		m_vVelocity.y = (m_vVelocity.y / abs(m_vVelocity.y)) * m_fMaxDown;
	}


	// 물체에 적용되고있는 힘이 없으면 마찰력을 적용시킨다.
	if (m_vForce.IsZero() && m_vVelocity.x != 0.f && m_bGround)
	{
		float fFriction = -m_vVelocity.x;
		fFriction /= abs(fFriction);

		fFriction *= m_fFrictionScale;

		float fFrictionAccel = (fFriction / m_fMass) * _DT;
		if (abs(m_vVelocity.x) < abs(fFrictionAccel))
		{
			m_vVelocity = Vec2(0.f, m_vVelocity.y);
		}
		else
		{
			m_vVelocity.x += fFrictionAccel;
		}
	}

	Vec2 vObjPos = GetOwner()->GetPos();
	vObjPos += m_vVelocity * _DT;
	GetOwner()->SetPos(vObjPos);

	// 힘 리셋
	m_vForce = Vec2(0.f, 0.f);
}
