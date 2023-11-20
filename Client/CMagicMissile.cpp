#include "pch.h"
#include "CMagicMissile.h"

#include "CAssetMgr.h"
#include "CTexture.h"

CMagicMissile::CMagicMissile()
	: m_pAnimator(nullptr)
	, m_pCollider(nullptr)
	, m_bDir(true)
	, m_fAccel(15.f)
	, m_fVelocity(0.f)
{
	SetScale(Vec2(2.f, 2.f));

	m_pAnimator = AddComponent<CAnimator>(L"MagicMissile");

	// Spawn
	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"pope_magicMissile", L"texture\\Effect\\pope_magicMissile.png");
	CTexture* pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"pope_magicMissile_L", L"texture\\Effect\\pope_magicMissile.png");

	m_pAnimator->LoadAnimation(pTex, L"Spawn", L"animdata\\Effect\\pope_magicMissileSpawn.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Spawn_L", L"animdata\\Effect\\pope_magicMissileSpawn.txt", true);


	m_pAnimator->SetAnimDuration(L"Spawn", 0.06f);
	m_pAnimator->SetAnimDuration(L"Spawn_L", 0.06f);


	// Imapct
	m_pAnimator->LoadAnimation(pTex, L"Impact", L"animdata\\Effect\\pope_magicMissileImpact.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Impact_L", L"animdata\\Effect\\pope_magicMissileImpact.txt", true);


	m_pAnimator->SetAnimDuration(L"Impact", 0.06f);
	m_pAnimator->SetAnimDuration(L"Impact_L", 0.06f);


	// Collider
	m_pCollider = AddComponent<CCollider>(L"MagicMissile");
	m_pCollider->SetScale(Vec2(50.f, 20.f));
	m_pCollider->SetOffsetPos(Vec2(0.f, 0.f));
	m_pCollider->SetTime(-1.f);
}

CMagicMissile::~CMagicMissile()
{
}

void CMagicMissile::On(Vec2 _vPos, bool _bDir)
{
	SetPos(_vPos);

	m_bIsOn = true;
	m_bDir = _bDir;

	m_eState = MAGICMISSILE::ACTIVE;

	if (m_bDir)
	{
		m_pAnimator->Play(L"Spawn", true);
		m_pCollider->SetOffsetPos(Vec2(80.f, 0.f));
	}
	else
	{
		m_pAnimator->Play(L"Spawn_L", true);
		m_pCollider->SetOffsetPos(Vec2(-80.f, 0.f));
	}

	m_pCollider->SetTime(10.f);
	m_pCollider->On();

	m_fVelocity = 0.f;

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

			if (m_bDir)
			{
				vPos += Vec2(1.f,0.f) * m_fVelocity * _DT;
			}
			else
			{
				vPos += Vec2(-1.f, 0.f) * m_fVelocity * _DT;
			}

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


}

void CMagicMissile::render(HDC _dc)
{
	Super::render(_dc);
}

void CMagicMissile::BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol)
{

	if (_pOtherObj->GetLayerIdx() == (UINT)LAYER::PLAYER)
	{
		m_eState = MAGICMISSILE::IMPACT;
		if (m_bDir)
		{
			m_pAnimator->Play(L"Impact", false);
		}
		else
		{
			m_pAnimator->Play(L"Impact_L", false);
		}

		// Collider Off
		m_pCollider->SetTime(0.f);
	}

}

