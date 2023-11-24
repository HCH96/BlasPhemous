#include "pch.h"
#include "CToxic.h"

#include "CAssetMgr.h"
#include "CTexture.h"

#include "CLevelMgr.h"
#include "CPenitent.h"

CToxic::CToxic()
	: m_pAnimator(nullptr)
	, m_pCollider(nullptr)
	, m_vDir(Vec2(1.f, 0.f))
	, m_fAccel(3.f)
	, m_fVelocity(10.f)
	, m_fAcc(0.f)
{
	SetScale(Vec2(2.f, 2.f));

	m_pAnimator = AddComponent<CAnimator>(L"Toxic");

	// Spawn
	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"pope_toxicOrb", L"texture\\Effect\\pope_toxicOrb.png");

	m_pAnimator->LoadAnimation(pTex, L"Spawn", L"animdata\\Effect\\pope_toxicOrbSpawn.txt");

	m_pAnimator->SetAnimDuration(L"Spawn", 0.06f);

	// Active

	m_pAnimator->LoadAnimation(pTex, L"Active", L"animdata\\Effect\\pope_toxicOrbActive.txt");

	m_pAnimator->SetAnimDuration(L"Active", 0.06f);


	// Imapct

	pTex = CAssetMgr::GetInst()->LoadTexture(L"Pope_toxicCloud", L"texture\\Effect\\Pope_toxicCloud.png");

	m_pAnimator->LoadAnimation(pTex, L"Impact", L"animdata\\Effect\\Pope_toxicCloud.txt");

	m_pAnimator->SetAnimDuration(L"Impact", 0.06f);


	// Collider
	m_pCollider = AddComponent<CCollider>(L"Toxic");
	m_pCollider->SetScale(Vec2(50.f, 50.f));
	m_pCollider->SetOffsetPos(Vec2(0.f, 0.f));
	m_pCollider->SetTime(0.5f);


}

CToxic::~CToxic()
{
}


void CToxic::On(Vec2 _vPos)
{
	SetPos(_vPos);
	SetDir(Vec2(1.f,0.f));

	m_bIsOn = true;
	m_fAcc = 0.f;


	m_eState = TOXIC::SPAWN;
	m_pAnimator->Play(L"Spawn", true);

	m_pCollider->SetTime(10.f);
	m_pCollider->On();

	m_fVelocity = 0.f;

	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"PURPLE_SPELL", L"sound\\Object\\Monster\\Boss\\Pontiff\\PURPLE_SPELL.wav");
	pSound->Play();

}

void CToxic::Off()
{
	// Collider Off
	m_pAnimator->Stop();
	m_pCollider->SetTime(0.f);
	m_bIsOn = false;

}

void CToxic::tick(float _DT)
{
	if (!m_bIsOn)
		return;

	Super::tick(_DT);

	// On 상태일 때
	if (m_bIsOn)
	{
		switch (m_eState)
		{
		case TOXIC::SPAWN:
		{
			if (m_pAnimator->IsFinish())
			{
				m_pAnimator->Play(L"Active", true);
				m_eState = TOXIC::ACTIVE;

				// Spawn이 끝나는 시점 Target 저장

				CObj* pTarget = CLevelMgr::GetInst()->GetPenitent();
				Vec2 vPos = GetPos();
				Vec2 vTargetDir = pTarget->GetPos();
				vTargetDir.y -= 100.f;


				Vec2 vDir = (vTargetDir - vPos).Normalize();

				m_vDir = vDir;
			}
		}

		break;
		case TOXIC::ACTIVE:
		{

			Vec2 vPos = GetPos();
			m_fVelocity = m_fVelocity + m_fAccel;
			vPos += m_vDir * m_fVelocity * _DT;

			SetPos(vPos);
		}

		break;
		case TOXIC::IMPACT:
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
		Off();
}

void CToxic::render(HDC _dc)
{
	if (!m_bIsOn)
		return;

	Super::render(_dc);
}

void CToxic::BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol)
{
	if (_pOtherObj->GetLayerIdx() == (UINT)LAYER::PLATFORM)
	{
		m_eState = TOXIC::IMPACT;
		m_pAnimator->Play(L"Impact", false);
	}

	if (_pOtherObj->GetLayerIdx() == (UINT)LAYER::PLAYER)
	{
		m_eState = TOXIC::IMPACT;
		m_pAnimator->Play(L"Impact", false);
	}

}

