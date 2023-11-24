#include "pch.h"
#include "CAshPlatform.h"

#include "CPenitent.h"

#include "CAssetMgr.h"
#include "CTexture.h"

CAshPlatform::CAshPlatform()
	: m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_fAcc(0.f)
	, m_eState(ASHSTATE::NONE)
{
	SetScale(Vec2(2.f, 2.f));
	 
	// Animator 
	m_pAnimator = AddComponent<CAnimator>(L"AshPlatform");

	// Appear
	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"AshApear", L"texture\\Object\\MetaObject\\bloodsand_platform_64x64_novisible_to_visible.png");
	m_pAnimator->LoadAnimation(pTex, L"Appear", L"animdata\\Object\\bloodsand_platform_64x64_novisible_to_visible.txt");
	m_pAnimator->SetAnimDuration(L"Appear", 0.06f);

	// Active
	pTex = CAssetMgr::GetInst()->LoadTexture(L"AshAnim", L"texture\\Object\\MetaObject\\ashplatform_64x64_anim.png");
	m_pAnimator->LoadAnimation(pTex, L"Active", L"animdata\\Object\\ashplatform_64x64_anim.txt");
	m_pAnimator->SetAnimDuration(L"Active", 0.06f);

	// Vanish
	pTex = CAssetMgr::GetInst()->LoadTexture(L"AshVanish", L"texture\\Object\\MetaObject\\bloodsand_platform_64x64_visible_to_novisible.png");
	m_pAnimator->LoadAnimation(pTex, L"Vanish", L"animdata\\Object\\bloodsand_platform_64x64_visible_to_novisible.txt");
	m_pAnimator->SetAnimDuration(L"Vanish", 0.06f);



	// Collider
	m_pCollider = AddComponent<CCollider>(L"AshPlatform");
	m_pCollider->SetScale(Vec2(120.f, 50.f));
	m_pCollider->SetOffsetPos(Vec2(0.f, 20.f));
	m_pCollider->SetTime(0.f);

}

CAshPlatform::CAshPlatform(const CAshPlatform& _Origin)
{
}

CAshPlatform::~CAshPlatform()
{
}



void CAshPlatform::tick(float _DT)
{
	Super::tick(_DT);

	m_fAcc += _DT;

	switch (m_eState)
	{
	case ASHSTATE::NONE:
	{
		// 사라진지 16초가 지났다면 다시 소환
		if (m_fAcc > 12.f)
		{
			m_eState = ASHSTATE::APPEAR;
			m_pAnimator->Play(L"Appear", false);
			m_fAcc = 0.f;
		}
	}

		break;
	case ASHSTATE::APPEAR:
	{
		if (m_pAnimator->GetCurFrame() == 6)
		{

			m_pCollider->SetTime(8.f);
			m_pCollider->On();
		}

		// Apear 애니메이션이 끝났다면 Active로 전환, Collider 활성화
		if (m_pAnimator->IsFinish())
		{
			m_eState = ASHSTATE::ACTIVE;
			m_pAnimator->Play(L"Active", true);
			
			
		}

	}

		break;
	case ASHSTATE::ACTIVE:
	{
		// 8초 활성화 되었다면 Vanish로 감 
		if (m_fAcc > 8.f)
		{
			m_eState = ASHSTATE::VANISH;
			m_pAnimator->Play(L"Vanish", false);
			
			m_fAcc = 0.f;
		}

	}
		break;
	case ASHSTATE::VANISH:
	{

		if (m_pAnimator->GetCurFrame() == 6)
		{
			m_pCollider->SetTime(0.f);
		}

		// 애니메이션이 끝났다면 Animation을 끄고 None상태로 감 Collider Off
		if (m_pAnimator->IsFinish())
		{
			m_eState = ASHSTATE::NONE;

			m_pAnimator->Stop();
		}

	}
		break;
	default:
		break;
	}



}


void CAshPlatform::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if (_OtherCol->GetName() != L"Penitent_Collider")
		return;

	CPenitent* pPenitent = dynamic_cast<CPenitent*>(_OtherObj);

	Vec2 vPos = _OwnCol->GetPos();
	Vec2 vScale = _OwnCol->GetScale();
	Vec2 vObjPos = _OtherObj->GetPos();
	CMovement* pOtherMovement = _OtherObj->GetComponent<CMovement>();

	float fAngle = m_pCollider->GetAngle();
	float radians = float(fAngle * (M_PI / 180.0f));

	float fTargetY = vPos.y + (vObjPos.x - vPos.x) * tan(radians);

	if (m_pCollider->GetAngle() == 0.f)
	{
		if (vObjPos.y > fTargetY && vPos.y + vScale.y / 2.f > vObjPos.y)
		{
			if (pOtherMovement->GetVelocity().y >= 0)
			{
				CPenitent* pPenitent = dynamic_cast<CPenitent*>(_OtherObj);
				_OtherObj->SetPos(Vec2(vObjPos.x, fTargetY));
				pOtherMovement->SetGround(true);
			}
		}
	}


}


