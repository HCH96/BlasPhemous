#include "pch.h"
#include "CMagicMissile.h"

#include "CAssetMgr.h"
#include "CTexture.h"

CMagicMissile::CMagicMissile()
	: m_pAnimator(nullptr)
	, m_pCollider(nullptr)
	, m_fAccel(15.f)
	, m_fVelocity(0.f)
	, m_vDir(Vec2(1.f,0.f))
	, m_fAcc(0.f)
{
	SetScale(Vec2(2.f, 2.f));

	m_pAnimator = AddComponent<CAnimator>(L"MagicMissile");

	// Spawn
	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"pope_magicMissile", L"texture\\Effect\\pope_magicMissile.png");

	m_pAnimator->LoadAnimation(pTex, L"Spawn", L"animdata\\Effect\\pope_magicMissileSpawn.txt");


	m_pAnimator->SetAnimDuration(L"Spawn", 0.06f);


	// Imapct
	m_pAnimator->LoadAnimation(pTex, L"Impact", L"animdata\\Effect\\pope_magicMissileImpact.txt");


	m_pAnimator->SetAnimDuration(L"Impact", 0.06f);


	// Collider
	m_pCollider = AddComponent<CCollider>(L"MagicMissile");
	m_pCollider->SetScale(Vec2(50.f, 20.f));
	m_pCollider->SetOffsetPos(Vec2(0.f, 0.f));
	m_pCollider->SetTime(-1.f);
}

CMagicMissile::~CMagicMissile()
{
}

void CMagicMissile::On(Vec2 _vPos, Vec2 _vDir)
{
	SetPos(_vPos);

	m_bIsOn = true;
	m_vDir = _vDir.Normalize();

	m_eState = MAGICMISSILE::ACTIVE;
	SetAngle(RadiansToDegrees(_vDir.ToRadian()));


	m_pAnimator->Play(L"Spawn", true);

	m_pCollider->SetOffsetPos(Vec2(80.f, 0.f).Rotate(GetAngle()));


	m_pCollider->SetTime(7.f);
	m_pCollider->On();

	m_fVelocity = 0.f;
	m_fAcc = 0.f;

}

void CMagicMissile::Off()
{
	// Collider Off
	m_pAnimator->Stop();
	m_bIsOn = false;
}

void CMagicMissile::tick(float _DT)
{
	if (!m_bIsOn)
		return;

	Super::tick(_DT);


	if (m_bIsOn)
	{
		switch (m_eState)
		{
		case MAGICMISSILE::ACTIVE:
		{
			Vec2 vPos = GetPos();

			m_fVelocity = m_fVelocity + m_fAccel;

			vPos += m_vDir * m_fVelocity * _DT;

			SetPos(vPos);

			if (m_pAnimator->GetCurFrame() == 20)
			{
				m_pAnimator->SetFrame(7);
			}

		}
			break;
		case MAGICMISSILE::IMPACT:
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

	if (m_fAcc > 5.f)
	{
		Off();
	}

}

void CMagicMissile::render(HDC _dc)
{
	if (!m_bIsOn)
		return;

	Super::render(_dc);
}

void CMagicMissile::BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol)
{

	if (_pOtherObj->GetLayerIdx() == (UINT)LAYER::PLAYER && _pOtherCol->GetName() == L"Penitent_Collider")
	{
		m_eState = MAGICMISSILE::IMPACT;

		//SetAngle(0.f);
		m_pAnimator->Play(L"Impact", false);

		// Collider Off
		m_pCollider->SetTime(0.f);
	}

}

