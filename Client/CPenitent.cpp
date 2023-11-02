#include "pch.h"
#include "CPenitent.h"

#include "CAssetMgr.h"
#include "CTexture.h"

CPenitent::CPenitent()
	: m_pAnimator(nullptr)
	, m_pCollider(nullptr)
	, m_pMovement(nullptr)
	, m_pSM(nullptr)
{
	// 이름 설정
	SetName(L"Penitent");

	// Animator init
	m_pAnimator = AddComponent<CAnimator>(L"Penitent_Animator");


	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"Idle", L"texture\\Penitent\\penintent_idle_anim 1.png");

	m_pAnimator->CreateAnimation(L"Idle", pTex, Vec2(15.f, 39.f), Vec2(70.f, 75.f), Vec2(0.f, 0.f), 0.1f, 1);
	SetScale(Vec2(2.f, 2.f));
	//m_pAnimator->SaveAnimations(L"animdata\\Penitent");
	m_pAnimator->Play(L"Idle",true);


}

CPenitent::CPenitent(const CPenitent& _Origin)
{
}

CPenitent::~CPenitent()
{
}


void CPenitent::tick(float _DT)
{
	Super::tick(_DT);
}

void CPenitent::BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol)
{
}

void CPenitent::EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
}


