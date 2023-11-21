#include "pch.h"
#include "CFirebolt.h"

#include "CAssetMgr.h"
#include "CTexture.h"

#include "CLevelMgr.h"
#include "CPenitent.h"


CFirebolt::CFirebolt()
	: m_pAnimator(nullptr)
	, m_pCollider(nullptr)
	, m_vDir(Vec2(1.f,0.f))
	, m_fAccel(20.f)
	, m_fVelocity(0.f)
{
	SetScale(Vec2(2.f, 2.f));

	m_pAnimator = AddComponent<CAnimator>(L"Firebolt");


	// Spawn
	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"Firebolt_Spawn", L"texture\\Effect\\pope_fireBallVortex.png");

	m_pAnimator->LoadAnimation(pTex, L"Spawn", L"animdata\\Effect\\pope_fireBallVortex.txt");

	m_pAnimator->SetAnimDuration(L"Spawn", 0.06f);

	// Active

	pTex = CAssetMgr::GetInst()->LoadTexture(L"Firebolt_Active", L"texture\\Effect\\pope_fireBall.png");

	m_pAnimator->LoadAnimation(pTex, L"Active", L"animdata\\Effect\\pope_fireBall.txt");

	m_pAnimator->SetAnimDuration(L"Active", 0.06f);


	// Imapct

	pTex = CAssetMgr::GetInst()->LoadTexture(L"Firebolt_Impact", L"texture\\Effect\\fireTrap_projectile_destroyed.png");

	m_pAnimator->LoadAnimation(pTex, L"Impact", L"animdata\\Effect\\fireTrap_projectile_destroyed.txt");

	m_pAnimator->SetAnimDuration(L"Impact", 0.06f);

	// Collider
	m_pCollider = AddComponent<CCollider>(L"Firebolt");
	m_pCollider->SetScale(Vec2(50.f, 50.f));
	m_pCollider->SetOffsetPos(Vec2(0.f, 0.f));
	m_pCollider->SetTime(0.5f);


}

CFirebolt::~CFirebolt()
{
}


void CFirebolt::On(Vec2 _vPos, Vec2 _vDir)
{
	SetPos(_vPos);
	SetDir(_vDir);

	m_bIsOn = true;
	m_vDir = _vDir.Normalize();

	SetAngle(RadiansToDegrees(_vDir.ToRadian()));


	m_eState = FIREBOLT::SPAWN;
	m_pAnimator->Play(L"Spawn", true);

	m_pCollider->SetTime(10.f);
	m_pCollider->On();

	m_fVelocity = 0.f;
}

void CFirebolt::Off()
{
	// Collider Off
	m_pAnimator->Stop();
	m_pCollider->SetTime(0.f);
	m_bIsOn = false;

}

void CFirebolt::tick(float _DT)
{
	if (!m_bIsOn)
		return;

	Super::tick(_DT);

	// On 상태일 때
	if (m_bIsOn)
	{
		switch (m_eState)
		{
		case FIREBOLT::SPAWN:
		{
			if (m_pAnimator->IsFinish())
			{
				m_pAnimator->Play(L"Active", true);
				m_eState = FIREBOLT::ACTIVE;

				// Spawn이 끝나는 시점 Target 저장

				CObj* pTarget = CLevelMgr::GetInst()->GetPenitent();
				Vec2 vPos = GetPos();
				Vec2 vTargetDir = pTarget->GetPos();
				vTargetDir.y -= 100.f;
				
				
				Vec2 vDir = (vTargetDir - vPos).Normalize();

				SetAngle(RadiansToDegrees(vDir.ToRadian()));

				m_vDir = vDir;


			}
		}

		break;
		case FIREBOLT::ACTIVE:
		{

			Vec2 vPos = GetPos();
			m_fVelocity = m_fVelocity + m_fAccel;
			vPos += m_vDir * m_fVelocity * _DT;

			SetPos(vPos);



		}

			break;
		case FIREBOLT::IMPACT:
		{
			m_pCollider->SetTime(0.f);
			if (m_pAnimator->IsFinish())
			{
				Off();
			}
		}

			break;
		default:
			break;
		}


	}

}

void CFirebolt::render(HDC _dc)
{
	Super::render(_dc);
}

void CFirebolt::BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol)
{
	if (_pOtherObj->GetLayerIdx() == (UINT)LAYER::PLATFORM)
	{
		m_eState = FIREBOLT::IMPACT;
		m_pAnimator->Play(L"Impact", false);
	} 

	if (_pOtherObj->GetLayerIdx() == (UINT)LAYER::PLAYER && _pOtherCol->GetName() == L"Penitent_Collider")
	{
		Off();
	}
}

