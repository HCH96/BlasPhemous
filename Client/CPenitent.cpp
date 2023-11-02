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

	// 배율 설정
	SetScale(Vec2(2.f, 2.f));

	// Animator init
	m_pAnimator = AddComponent<CAnimator>(L"Penitent_Animator");


	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"Idle", L"texture\\Penitent\\penintent_idle_anim 1.png");

	// Load Meta
	m_pAnimator->LoadAnimation(pTex, L"Idle", L"animdata\\Penitent\\penitent_idle_anim.txt");
	m_pAnimator->Play(L"Idle", true);




	//m_pAnimator->CreateAnimation(L"Idle", pTex, Vec2(15.f, 39.f), Vec2(70.f, 75.f), Vec2(0.f, 0.f), 0.1f, 13);
	//m_pAnimator->SaveAnimations(L"animdata\\Penitent");
	//m_pAnimator->LoadAnimation(L"\\animdata\\Penitent\\Idle.txt");

	//m_pAnimator->Play(L"Idle",true);


}

CPenitent::CPenitent(const CPenitent& _Origin)
	: CObj(_Origin)
	, m_pAnimator(nullptr)
	, m_pCollider(nullptr)
	, m_pMovement(nullptr)
	, m_pSM(nullptr)
{
	m_pCollider = GetComponent<CCollider>();
	m_pAnimator = GetComponent<CAnimator>();
	m_pMovement = GetComponent<CMovement>();
	m_pSM = GetComponent<CStateMachine>();
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


