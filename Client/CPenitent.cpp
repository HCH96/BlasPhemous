#include "pch.h"
#include "CPenitent.h"

#include "CAssetMgr.h"
#include "CTexture.h"

#include "CPlatform.h"

#include "CPenitentIdle.h"
#include "CPenitentStartRun.h"
#include "CPenitentRun.h"
#include "CPenitentStopRun.h"
#include "CPenitentJump.h"
#include "CPenitentFall.h"
#include "CPenitentJumpForward.h"
#include "CPenitentFowardFall.h"


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
	AnimationInit();

	// collider
	m_pCollider = AddComponent<CCollider>(L"Penitent_Collider");
	m_pCollider->SetOffsetPos(Vec2(0.f, -40.f));
	m_pCollider->SetScale(Vec2(40.f, 80.f));


	// StateMachine 컴포넌트 추가
	m_pSM = AddComponent<CStateMachine>(L"Penitent_SM");
	m_pSM->AddState((UINT)PENITENT_STATE::IDLE, new CPenitentIdle);
	m_pSM->AddState((UINT)PENITENT_STATE::STARTRRUN, new CPenitentStartRun);
	m_pSM->AddState((UINT)PENITENT_STATE::RUN, new CPenitentRun);
	m_pSM->AddState((UINT)PENITENT_STATE::STOPRUN, new CPenitentStopRun);
	m_pSM->AddState((UINT)PENITENT_STATE::JUMP, new CPenitentJump);
	m_pSM->AddState((UINT)PENITENT_STATE::FALL, new CPenitentFall);
	m_pSM->AddState((UINT)PENITENT_STATE::JUMPFORWARD, new CPenitentJumpForward);
	m_pSM->AddState((UINT)PENITENT_STATE::JUMPFORWARDFALL, new CPenitentFowardFall);

	m_pSM->ChangeState((UINT)PENITENT_STATE::IDLE);




	// Movement 컴포넌트 추가
	m_pMovement = AddComponent<CMovement>(L"Penitent_Movement");
	m_pMovement->SetMass(1.f);
	m_pMovement->SetInitSpeed(200.f);
	m_pMovement->SetMaxSpeed(300.f);
	m_pMovement->SetFrictionScale(1500.f);
	m_pMovement->UseGravity(true);
	m_pMovement->SetGravity(Vec2(0.f, 1600.f));
	m_pMovement->SetJumpVel(-600.f);
	m_pMovement->SetMaxDown(500.f);

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




void CPenitent::begin()
{
	
}

void CPenitent::tick(float _DT)
{
	Super::tick(_DT);

	// 방향 설정
	if ((KEY_TAP(KEY::LEFT) || KEY_PRESSED(KEY::LEFT)) && KEY_NONE(KEY::RIGHT))
	{
		SetPrevDir(GetDir());
		SetDir(false);

	}

	if ((KEY_TAP(KEY::RIGHT) || KEY_PRESSED(KEY::RIGHT)) && KEY_NONE(KEY::LEFT))
	{
		SetPrevDir(GetDir());
		SetDir(true);
	}


}

void CPenitent::BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol)
{
	if (dynamic_cast<CPlatform*>(_pOtherObj))
	{
		m_pMovement->SetGround(true);
	}
}

void CPenitent::EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if (dynamic_cast<CPlatform*>(_OtherObj))
	{
		m_pMovement->SetGround(false);
	}
}

void CPenitent::AnimationInit()
{
	// Idle
	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"Idle", L"texture\\Penitent\\penintent_idle_anim 1.png");
	CTexture* pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Idle_L", L"texture\\Penitent\\penintent_idle_anim 1.png");

	m_pAnimator->LoadAnimation(pTex, L"Idle", L"animdata\\Penitent\\penitent_idle_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Idle_L", L"animdata\\Penitent\\penitent_idle_anim.txt", true);

	//Death
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Death", L"texture\\Penitent\\death_anim_blood.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Death_L", L"texture\\Penitent\\death_anim_blood.png");

	m_pAnimator->LoadAnimation(pTex, L"Death", L"animdata\\Penitent\\death_anim_blood.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Death_L", L"animdata\\Penitent\\death_anim_blood.txt", true);

	m_pAnimator->SetAnimDuration(L"Death", 0.08f);
	m_pAnimator->SetAnimDuration(L"Death_L", 0.08f);

	//ThrowBack
	pTex = CAssetMgr::GetInst()->LoadTexture(L"ThrowBack", L"texture\\Penitent\\penitent_throwback_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"ThrowBack_L", L"texture\\Penitent\\penitent_throwback_anim.png");

	m_pAnimator->LoadAnimation(pTex, L"ThrowBack", L"animdata\\Penitent\\penitent_throwback_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"ThrowBack_L", L"animdata\\Penitent\\penitent_throwback_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"ThrowBack", 0.08f);
	m_pAnimator->SetAnimDuration(L"ThrowBack_L", 0.08f);

	//UpwardAttck_Jump
	pTex = CAssetMgr::GetInst()->LoadTexture(L"UpwardAttck_Jump", L"texture\\Penitent\\penitent_upward_attack_jump.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"UpwardAttck_Jump_L", L"texture\\Penitent\\penitent_upward_attack_jump.png");

	m_pAnimator->LoadAnimation(pTex, L"UpwardAttck_Jump", L"animdata\\Penitent\\penitent_upward_attack_jump.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"UpwardAttck_Jump_L", L"animdata\\Penitent\\penitent_upward_attack_jump.txt", true);

	m_pAnimator->SetAnimDuration(L"UpwardAttck_Jump", 0.08f);
	m_pAnimator->SetAnimDuration(L"UpwardAttck_Jump_L", 0.08f);


	//UpwardAttck
	pTex = CAssetMgr::GetInst()->LoadTexture(L"UpwardAttck", L"texture\\Penitent\\penitent_upward_attack_clamped_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"UpwardAttck_L", L"texture\\Penitent\\penitent_upward_attack_clamped_anim.png");

	m_pAnimator->LoadAnimation(pTex, L"UpwardAttck", L"animdata\\Penitent\\penitent_upward_attack_clamped_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"UpwardAttck_L", L"animdata\\Penitent\\penitent_upward_attack_clamped_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"UpwardAttck", 0.08f);
	m_pAnimator->SetAnimDuration(L"UpwardAttck_L", 0.08f);


	// Atack
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Attack", L"texture\\Penitent\\penitent_three_hits_attack_combo_no_slashes.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Attack_L", L"texture\\Penitent\\penitent_three_hits_attack_combo_no_slashes.png");

	m_pAnimator->LoadAnimation(pTex, L"Attack", L"animdata\\Penitent\\penitent_three_hits_attack_combo_no_slashes.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Attack_L", L"animdata\\Penitent\\penitent_three_hits_attack_combo_no_slashes.txt", true);

	m_pAnimator->SetAnimDuration(L"Attack", 0.08f);
	m_pAnimator->SetAnimDuration(L"Attack_L", 0.08f);


	// run

	pTex = CAssetMgr::GetInst()->LoadTexture(L"Run", L"texture\\Penitent\\penitent_running_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Run_L", L"texture\\Penitent\\penitent_running_anim.png");


	m_pAnimator->LoadAnimation(pTex, L"Run", L"animdata\\Penitent\\penitent_running_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Run_L", L"animdata\\Penitent\\penitent_running_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"Run", 0.06f);
	m_pAnimator->SetAnimDuration(L"Run_L", 0.06f);



	//penitent_risingFromFallen_anim

	pTex = CAssetMgr::GetInst()->LoadTexture(L"Rising", L"texture\\Penitent\\penitent_risingFromFallen_anim.png");
	//pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Run_L", L"texture\\Penitent\\penitent_running_anim.png");


	m_pAnimator->LoadAnimation(pTex, L"Rising", L"animdata\\Penitent\\penitent_risingFromFallen_anim.txt");
	//m_pAnimator->LoadAnimation(pTexReverse, L"Run_L", L"animdata\\Penitent\\penitent_running_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"Rising", 0.05f);
	//m_pAnimator->SetAnimDuration(L"Run_L", 0.06f);


	// Penitent_pushback_grounded
	pTex = CAssetMgr::GetInst()->LoadTexture(L"PushBack", L"texture\\Penitent\\Penitent_pushback_grounded.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"PushBack_L", L"texture\\Penitent\\Penitent_pushback_grounded.png");


	m_pAnimator->LoadAnimation(pTex, L"PushBack", L"animdata\\Penitent\\Penitent_pushback_grounded.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"PushBack_L", L"animdata\\Penitent\\Penitent_pushback_grounded.txt", true);

	m_pAnimator->SetAnimDuration(L"PushBack", 0.06f);
	m_pAnimator->SetAnimDuration(L"PushBack_L", 0.06f);


	// penitent_priedieu_stand_up_anim
	pTex = CAssetMgr::GetInst()->LoadTexture(L"PrayEnd", L"texture\\Penitent\\penitent_priedieu_stand_up_anim.png");
	//pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Run_L", L"texture\\Penitent\\penitent_running_anim.png");


	m_pAnimator->LoadAnimation(pTex, L"PrayEnd", L"animdata\\Penitent\\penitent_priedieu_stand_up_anim.txt");
	//m_pAnimator->LoadAnimation(pTexReverse, L"Run_L", L"animdata\\Penitent\\penitent_running_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"PrayEnd", 0.05f);
	//m_pAnimator->SetAnimDuration(L"Run_L", 0.06f);



	// penintent_start_run_anim
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Start_Run", L"texture\\Penitent\\penintent_start_run_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Start_Run_L", L"texture\\Penitent\\penintent_start_run_anim.png");


	m_pAnimator->LoadAnimation(pTex, L"Start_Run", L"animdata\\Penitent\\penintent_start_run_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Start_Run_L", L"animdata\\Penitent\\penintent_start_run_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"Start_Run", 0.03f);
	m_pAnimator->SetAnimDuration(L"Start_Run_L", 0.03f);



	// penintent_stop_run_anim

	pTex = CAssetMgr::GetInst()->LoadTexture(L"Stop_Run", L"texture\\Penitent\\penintent_stop_run_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Stop_Run_L", L"texture\\Penitent\\penintent_stop_run_anim.png");


	m_pAnimator->LoadAnimation(pTex, L"Stop_Run", L"animdata\\Penitent\\penintent_stop_run_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Stop_Run_L", L"animdata\\Penitent\\penintent_stop_run_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"Stop_Run", 0.06f);
	m_pAnimator->SetAnimDuration(L"Stop_Run_L", 0.06f);

	// penitent_jump_anim

	pTex = CAssetMgr::GetInst()->LoadTexture(L"Jump", L"texture\\Penitent\\penitent_jump_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Jump_L", L"texture\\Penitent\\penitent_jump_anim.png");


	m_pAnimator->LoadAnimation(pTex, L"Jump", L"animdata\\Penitent\\penitent_jump_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Jump_L", L"animdata\\Penitent\\penitent_jump_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"Jump", 0.1f);
	m_pAnimator->SetAnimDuration(L"Jump_L", 0.1f);


	// Fall

	pTex = CAssetMgr::GetInst()->LoadTexture(L"Fall", L"texture\\Penitent\\penitent_falling_loop_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Fall_L", L"texture\\Penitent\\penitent_falling_loop_anim.png");


	m_pAnimator->LoadAnimation(pTex, L"Fall", L"animdata\\Penitent\\penitent_falling_loop_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Fall_L", L"animdata\\Penitent\\penitent_falling_loop_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"Fall", 0.05f);
	m_pAnimator->SetAnimDuration(L"Fall_L", 0.05f);

	// penitent_jum_forward_anim

	pTex = CAssetMgr::GetInst()->LoadTexture(L"JumpForward", L"texture\\Penitent\\penitent_jum_forward_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"JumpForward_L", L"texture\\Penitent\\penitent_jum_forward_anim.png");

	m_pAnimator->LoadAnimation(pTex, L"JumpForward", L"animdata\\Penitent\\penitent_jum_forward_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"JumpForward_L", L"animdata\\Penitent\\penitent_jum_forward_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"JumpForward", 0.1f);
	m_pAnimator->SetAnimDuration(L"JumpForward_L", 0.1f);

	//penitent_jum_forward_fall
		
	m_pAnimator->LoadAnimation(pTex, L"JumpForwardFall", L"animdata\\Penitent\\penitent_jum_forward_fall.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"JumpForwardFall_L", L"animdata\\Penitent\\penitent_jum_forward_fall.txt", true);

	m_pAnimator->SetAnimDuration(L"JumpForwardFall", 0.05f);
	m_pAnimator->SetAnimDuration(L"JumpForwardFall_L", 0.05f);


	m_pAnimator->Play(L"JumpForward", true);

	//m_pAnimator->SaveAnimations(L"animdata");
}
