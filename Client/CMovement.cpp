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

	// ���ӵ� ���
	m_vAccel = m_vForce / m_fMass;

	// �߷� ���
	if (m_bUseGravity && !m_bGround)
	{
		m_vAccel += m_vGravityForce;
	}

	// ������ ����� ������ ��� �ʱ�ӵ� �ֱ� (x�� ���⸸)
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

	// �ִ� �ӵ� ����
	if (abs(m_vVelocity.x) > m_fMaxSpeed)
	{
		m_vVelocity.x = (m_vVelocity.x / abs(m_vVelocity.x)) * m_fMaxSpeed;
	}

	if (m_vVelocity.y > m_fMaxDown)
	{
		m_vVelocity.y = (m_vVelocity.y / abs(m_vVelocity.y)) * m_fMaxDown;
	}


	// ��ü�� ����ǰ��ִ� ���� ������ �������� �����Ų��.
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

	// �� ����
	m_vForce = Vec2(0.f, 0.f);
}
