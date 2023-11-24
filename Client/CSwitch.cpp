#include "pch.h"
#include "CSwitch.h"

#include "CAssetMgr.h"
#include "CTexture.h"


#include "CCage.h"

CSwitch::CSwitch(CCage* _Cage)
	: m_pAnimator(nullptr)
	, m_pCollider(nullptr)
	, m_pCage(_Cage)
{
	// Animator
	m_pAnimator = AddComponent<CAnimator>(L"Switch");
	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"glassSwitch", L"texture\\Object\\glassSwitch.png");

	m_pAnimator->LoadAnimation(pTex, L"SwitchIdle", L"animdata\\Object\\SwitchIdle.txt");
	m_pAnimator->SetAnimDuration(L"SwitchIdle", 0.1f);

	m_pAnimator->LoadAnimation(pTex, L"SwitchOn", L"animdata\\Object\\SwitchOn.txt");
	m_pAnimator->SetAnimDuration(L"SwitchOn", 0.05f);


	m_pAnimator->Play(L"SwitchIdle", true);

	// Collider
	m_pCollider = AddComponent<CCollider>(L"Switch");
	m_pCollider->SetScale(Vec2(100.f, 100.f));
	m_pCollider->SetOffsetPos(Vec2(0.f, 80.f));

}

CSwitch::~CSwitch()
{
}

void CSwitch::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if (_OtherCol->GetName() == L"Penitent_HitBox")
	{
		m_pCage->Open();
		m_pAnimator->Play(L"SwitchOn", false);
	}

	m_pCollider->Off();

	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"GLASS_PLATFORM_COLLAPSE_C", L"sound\\Effect\\GLASS_PLATFORM_COLLAPSE_C.wav");
	pSound->Play();

}


