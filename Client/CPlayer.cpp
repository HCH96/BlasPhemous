#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTaskMgr.h"
#include "CAssetMgr.h"

#include "components.h"

#include "CProjectile.h"
#include "CPlatform.h"



CPlayer::CPlayer()
	: m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_pMovement(nullptr)
{
	SetName(L"Player");

	//CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"PlayerAtlas", L"texture\\link_alpha.bmp");
	// animator
	m_pAnimator = AddComponent<CAnimator>(L"Animator");

	// Create
	//m_pAnimator->CreateAnimation(L"WalkDown", pAtlas, Vec2(0.f, 520.f), Vec2(120, 130), Vec2(0.f,-60.f), 0.05f, 10);
	//m_pAnimator->CreateAnimation(L"WalkLeft", pAtlas, Vec2(0.f, 650.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 10);
	//m_pAnimator->CreateAnimation(L"WalkUp", pAtlas, Vec2(0.f, 780.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 10);
	//m_pAnimator->CreateAnimation(L"WalkRight", pAtlas, Vec2(0.f, 910.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 10);

	//m_pAnimator->CreateAnimation(L"IdleDown", pAtlas, Vec2(0.f, 0.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 3);
	//m_pAnimator->CreateAnimation(L"IdleLeft", pAtlas, Vec2(0.f, 130.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 3);
	//m_pAnimator->CreateAnimation(L"IdleUp", pAtlas, Vec2(0.f, 260.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 1);
	//m_pAnimator->CreateAnimation(L"IdleRight", pAtlas, Vec2(0.f, 390.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 3);
	// Save
	//m_pAnimator->SaveAnimations(L"animdata");


	m_pAnimator->LoadAnimation(L"animdata\\IdleDown.txt");
	m_pAnimator->LoadAnimation(L"animdata\\IdleLeft.txt");
	m_pAnimator->LoadAnimation(L"animdata\\IdleRight.txt");
	m_pAnimator->LoadAnimation(L"animdata\\IdleUp.txt");
	m_pAnimator->LoadAnimation(L"animdata\\WalkDown.txt");
	m_pAnimator->LoadAnimation(L"animdata\\WalkLeft.txt");
	m_pAnimator->LoadAnimation(L"animdata\\WalkRight.txt");
	m_pAnimator->LoadAnimation(L"animdata\\WalkUp.txt");

	m_pAnimator->Play(L"WalkDown", true);

	// collider
	m_pCollider = AddComponent<CCollider>(L"PlayerCollider");
	m_pCollider->SetOffsetPos(Vec2(0.f, -40.f));
	m_pCollider->SetScale(Vec2(40.f, 80.f));

	// Movement 컴포넌트 추가
	m_pMovement = AddComponent<CMovement>(L"PlayerMovement");
	m_pMovement->SetMass(1.f);
	m_pMovement->SetInitSpeed(200.f);
	m_pMovement->SetMaxSpeed(400.f);
	m_pMovement->SetFrictionScale(1000.f);
	m_pMovement->UseGravity(true);
	m_pMovement->SetGravity(Vec2(0.f, 980.f));

}

CPlayer::CPlayer(const CPlayer& _Origin)
	: CObj(_Origin)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_pMovement(nullptr)
{
	m_pCollider = GetComponent<CCollider>();
	m_pAnimator = GetComponent<CAnimator>();
	m_pMovement = GetComponent<CMovement>();

}

CPlayer::~CPlayer()
{

}



void CPlayer::tick(float _DT)
{
	Super::tick(_DT);

	Vec2 vPos = GetPos();
	
	if (KEY_PRESSED(KEY::W))
	{
		m_pAnimator->Play(L"WalkUp", true);
	}
	if (KEY_RELEASED(KEY::W))
	{
		m_pAnimator->Play(L"IdleUp", true);
	}

	if (KEY_PRESSED(KEY::S))
	{
		m_pAnimator->Play(L"WalkDown", true);
	}
	if (KEY_RELEASED(KEY::S))
	{
		m_pAnimator->Play(L"IdleDown", true);
	}
	
	if (KEY_PRESSED(KEY::A))
	{
		m_pMovement->AddForce(Vec2(-300.f, 0.f));
		m_pAnimator->Play(L"WalkLeft", true);
	}
	if (KEY_RELEASED(KEY::A))
	{
		m_pAnimator->Play(L"IdleLeft", true);
	}
	
	if (KEY_PRESSED(KEY::D))
	{
		m_pMovement->AddForce(Vec2(300.f, 0.f));
		m_pAnimator->Play(L"WalkRight", true);
	}
	if (KEY_RELEASED(KEY::D))
	{
		m_pAnimator->Play(L"IdleRight", true);
	}

	if (KEY_TAP(KEY::SPACE))
	{
		m_pMovement->SetGround(false);

		m_pMovement->SetVelocity(Vec2(m_pMovement->GetVelocity().x, -500.f));


		//CProjectile* pProjectile = new CProjectile;

		//Vec2 ProjectilePos = GetPos();
		//ProjectilePos.y -= GetScale().y / 2.f;

		//pProjectile->SetSpeed(1000.f);
		//pProjectile->SetDir(PI / 2.f);
		//pProjectile->SetPos(ProjectilePos);
		//pProjectile->SetScale(Vec2(25.f, 25.f));

		//CTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT)LAYER::PLAYER_PJ, (UINT_PTR)pProjectile });

	}

	SetPos(vPos);
}


void CPlayer::BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol)
{
	if (dynamic_cast<CPlatform*>(_pOtherObj))
	{
		m_pMovement->SetGround(true);
	}
}

void CPlayer::EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if (dynamic_cast<CPlatform*>(_OtherObj))
	{
		m_pMovement->SetGround(false);
	}
}