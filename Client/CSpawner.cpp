#include "pch.h"
#include "CSpawner.h"

#include "CRayBeam.h"

CSpawner::CSpawner()
	: m_bIsOn(false)
	, m_bDir(true)
	, m_fLifeTime(0.9f)
	, m_fAcc(0.f)
	, m_pMovement(nullptr)
	, m_pCollider(nullptr)
	, m_vecRayBeam{}
	, m_fCooltime(0.f)
	, m_iCurRay(0)
{
	m_pMovement = AddComponent<CMovement>(L"Spawner");
	m_pMovement->SetMass(1.f);
	m_pMovement->SetMaxSpeed(800.f);
	m_pMovement->SetFrictionScale(1.f);
	m_pMovement->UseGravity(true);
	m_pMovement->SetGravity(Vec2(0.f, 10000.f));
	m_pMovement->SetGround(false);
	m_pMovement->SetMaxDown(1000.f);


	m_pCollider = AddComponent<CCollider>(L"Spawner");
	m_pCollider->SetScale(Vec2(100.f, 100.f));
	m_pCollider->SetOffsetPos(Vec2(0.f, -50.f));

	m_vecRayBeam.reserve(10);
}

CSpawner::~CSpawner()
{
}


void CSpawner::On(Vec2 _vPos, bool _bDir)
{
	SetPos(_vPos);
	SetDir(_bDir);

	m_pCollider->SetFinalPos(_vPos);
	
	m_bIsOn = true;
	m_fAcc = 0.f;
	m_iCurRay = 0;
	m_fCooltime = 0.f;

}

void CSpawner::Off()
{
	SetPos(Vec2(0.f, 0.f));
	m_bIsOn = false;
}

void CSpawner::tick(float _DT)
{
	if (!m_bIsOn)
	{
		m_pMovement->SetVelocity(Vec2(0.f, 0.f));
		return;
	}

	Super::tick(_DT);


	if (m_fAcc > m_fLifeTime)
	{
		Off();
	}
	else
	{
		m_fAcc += _DT;
		m_fCooltime += _DT;


		Vec2 vPos = GetPos();

		if (GetDir())
		{
			m_pMovement->SetVelocity(Vec2(800.f, 0.f));
		}
		else
		{
			m_pMovement->SetVelocity(Vec2(-800.f, 0.f));
		}

		if (m_fCooltime > 0.1f)
		{
			if (m_iCurRay < m_vecRayBeam.size())
			{
				m_vecRayBeam[m_iCurRay]->On(GetPos(), GetDir());
				m_fCooltime = 0.f;
				m_iCurRay++;
			}
		}

	}



}

void CSpawner::render(HDC _dc)
{
	//if (!m_bIsOn)
	//	return;

	Super::render(_dc);

}


