#include "pch.h"
#include "CPenitent.h"

#include "CEngine.h"

#include "CTimeMgr.h"
#include "CAssetMgr.h"
#include "CTexture.h"

#include "CPlatform.h"
#include "CLedge.h"


// State
#include "CPenitentFallingAhead.h"
#include "CPenitentRising.h"
#include "CPenitentIdle.h"
#include "CPenitentStartRun.h"
#include "CPenitentRun.h"
#include "CPenitentStopRun.h"
#include "CPenitentJump.h"
#include "CPenitentFall.h"
#include "CPenitentJumpForward.h"
#include "CPenitentFowardFall.h"
#include "CPenitentAttack.h"
#include "CPenitentUpwardATT.h"
#include "CPenitentUpwardATTJump.h"
#include "CPenitentDodge.h"
#include "CPenitentDodgeToRun.h"
#include "CPenitentJumpAttack.h"
#include "CPenitentHealthPotion.h"
#include "CPenitentCrouch.h"
#include "CPenitentCrouching.h"
#include "CPenitentCrouchUp.h"
#include "CPenitentCrouchATT.h"
#include "CPenitentDeath.h"
#include "CPenitentNone.h"
#include "CPenitentPrayStart.h"
#include "CPenitentPraying.h"
#include "CPenitentPrayAuraOff.h"
#include "CPenitentPrayEnd.h"
#include "CPenitentStanding.h"
#include "CPenitentCharging.h"
#include "CPenitentClimb.h"
#include "CPenitentHangOn.h"
#include "CPenitentLadder.h"
#include "CPenitentLadderDown.h"
#include "CPenitentLadderUp.h"
#include "CPenitentPushBack.h"



CPenitent::CPenitent()
	: m_pAnimator(nullptr)
	, m_pEffector(nullptr)
	, m_pCollider(nullptr)
	, m_pMovement(nullptr)
	, m_pDustAnimator(nullptr)
	, m_pSM(nullptr)
	, m_fHP(100.f)
	, m_iMP(3)
	, m_iPotion(3)
	, m_iOverlapGround(0)
	, m_fTears(0.f)
	, m_bIsLeft(true)
	, m_bDownPlatform(false)
	, m_iCheckPoint((UINT)LEVEL_TYPE::STAGE01_1)
{
	// 이름 설정
	SetName(L"Penitent");

	// 배율 설정
	SetScale(Vec2(2.f, 2.f));

	// Animator init
	
	// Penitent
	m_pAnimator = AddComponent<CAnimator>(L"Penitent_Animator");
	AnimationInit();
	
	// Effector
	m_pEffector = AddComponent<CAnimator>(L"Penitent_Effector");
	EffectInit();

	// Dust
	m_pDustAnimator = AddComponent<CAnimator>(L"Dust_Animator");
	DustAnimInit();

	
	// Movement 컴포넌트 추가
	m_pMovement = AddComponent<CMovement>(L"Penitent_Movement");
	m_pMovement->SetMass(1.f);
	m_pMovement->SetInitSpeed(300.f);
	m_pMovement->SetMaxSpeed(350.f);
	m_pMovement->SetFrictionScale(2000.f);
	m_pMovement->UseGravity(true);
	m_pMovement->SetGravity(Vec2(0.f, 2000.f));
	m_pMovement->SetJumpVel(-800.f);
	m_pMovement->SetMaxDown(1000.f);


	// StateMachine 컴포넌트 추가
	m_pSM = AddComponent<CStateMachine>(L"Penitent_SM");
	StateInit();

	// BackBorad 저장
	m_pSM->AddDataToBlackboard<bool>(L"IsTapS", false);


	
	
	// collider
	m_pCollider = AddComponent<CCollider>(L"Penitent_Collider");
	m_pCollider->SetScale(Vec2(40.f, 100.f));
	m_pCollider->SetOffsetPos(Vec2(0.f, -50.f));

	// HitBox
	m_pHitBox = AddComponent<CCollider>(L"Penitent_HitBox");
	m_pHitBox->Off();

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
	// 레벨 진입 시
	
	// Movement 세팅
	m_pMovement->SetGround(false);
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

	// DEBUG


	if (KEY_TAP(KEY::Q))
	{
		m_fHP = 0.f;
	}

	if (KEY_TAP(KEY::P))
	{
		m_fHP -= 20.f;
	}
	if (KEY_TAP(KEY::O) && m_iMP > 0)
	{
		--m_iMP;
	}

	if (KEY_TAP(KEY::I) && m_iMP < 3 )
	{
		++m_iMP;
	}

	if (KEY_TAP(KEY::U))
	{
		m_fTears += 100;
		CCamera::GetInst()->Shake(0.1f,0.5f);
	}


	Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;

	if (KEY_TAP(KEY::ENTER))
	{
		SetPos(vLookAt);
	}

	if (KEY_TAP(KEY::L))
	{
		m_pSM->ChangeState((UINT)PENITENT_STATE::LADDERDOWN);
	}

}

void CPenitent::OnDamaged()
{
	m_pSM->ChangeState((UINT)PENITENT_STATE::PUSHBACK);

}

void CPenitent::BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol)
{
	// 몬스터 Hit
	if (_pOwnCol->GetName() == L"Penitent_HitBox" && _pOtherObj->GetLayerIdx() == (UINT)LAYER::MONSTER)
	{
		CTimeMgr::GetInst()->Delay();
		CCamera::GetInst()->Shake(0.1f,0.5f);
	}

	// 피격
	if (_pOwnCol->GetName() == L"Penitent_Collider" && _pOtherObj->GetLayerIdx() == (UINT)LAYER::MONSTER)
	{
		OnDamaged();
	}


	// Platform
	if (dynamic_cast<CPlatform*>(_pOtherObj))
	{
		++m_iOverlapGround;
	}

}

void CPenitent::EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if (dynamic_cast<CPlatform*>(_OtherObj))
	{
		--m_iOverlapGround;
		SetDownPlatform(false);

		if (m_iOverlapGround <= 0)
		{
			m_pMovement->SetGround(false);
		}
	}

	//if (dynamic_cast<CLedge*>(_OtherObj))
	//{
	//	m_pMovement->SetGround(false);
	//	
	//}

}

void CPenitent::AnimationInit()
{
	
	// ================
	//    정적 State
	// ================
	
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

	m_pAnimator->SetAnimDuration(L"Death", 0.05f);
	m_pAnimator->SetAnimDuration(L"Death_L", 0.05f);

	//ThrowBack
	pTex = CAssetMgr::GetInst()->LoadTexture(L"ThrowBack", L"texture\\Penitent\\penitent_throwback_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"ThrowBack_L", L"texture\\Penitent\\penitent_throwback_anim.png");

	m_pAnimator->LoadAnimation(pTex, L"ThrowBack", L"animdata\\Penitent\\penitent_throwback_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"ThrowBack_L", L"animdata\\Penitent\\penitent_throwback_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"ThrowBack", 0.08f);
	m_pAnimator->SetAnimDuration(L"ThrowBack_L", 0.08f);

	// Healthpotion
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Healthpotion", L"texture\\Penitent\\penitent_healthpotion_consuming_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Healthpotion_L", L"texture\\Penitent\\penitent_healthpotion_consuming_anim.png");

	m_pAnimator->LoadAnimation(pTex, L"Healthpotion", L"animdata\\Penitent\\penitent_healthpotion_consuming_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Healthpotion_L", L"animdata\\Penitent\\penitent_healthpotion_consuming_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"Healthpotion", 0.05f);
	m_pAnimator->SetAnimDuration(L"Healthpotion_L", 0.05f);


	// Rising

	pTex = CAssetMgr::GetInst()->LoadTexture(L"Rising", L"texture\\Penitent\\penitent_risingFromFallen_anim.png");
	m_pAnimator->LoadAnimation(pTex, L"Rising", L"animdata\\Penitent\\penitent_risingFromFallen_anim.txt");
	m_pAnimator->SetAnimDuration(L"Rising", 0.1f);


	// PushBack
	pTex = CAssetMgr::GetInst()->LoadTexture(L"PushBack", L"texture\\Penitent\\Penitent_pushback_grounded.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"PushBack_L", L"texture\\Penitent\\Penitent_pushback_grounded.png");


	m_pAnimator->LoadAnimation(pTex, L"PushBack", L"animdata\\Penitent\\Penitent_pushback_grounded.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"PushBack_L", L"animdata\\Penitent\\Penitent_pushback_grounded.txt", true);

	m_pAnimator->SetAnimDuration(L"PushBack", 0.06f);
	m_pAnimator->SetAnimDuration(L"PushBack_L", 0.06f);

	// PrayStart
	pTex = CAssetMgr::GetInst()->LoadTexture(L"PrayStart", L"texture\\Penitent\\penitent_priedieu_kneeling_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"PrayStart_L", L"texture\\Penitent\\penitent_priedieu_kneeling_anim.png");


	m_pAnimator->LoadAnimation(pTex, L"PrayStart", L"animdata\\Penitent\\penitent_priedieu_kneeling_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"PrayStart_L", L"animdata\\Penitent\\penitent_priedieu_kneeling_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"PrayStart", 0.05f);
	m_pAnimator->SetAnimDuration(L"PrayStart_L", 0.05f);

	// Praying
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Praying", L"texture\\Penitent\\penitent_priedieu_bended_knee_with_aura.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Praying_L", L"texture\\Penitent\\penitent_priedieu_bended_knee_with_aura.png");


	m_pAnimator->LoadAnimation(pTex, L"Praying", L"animdata\\Penitent\\penitent_priedieu_bended_knee_with_aura.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Praying_L", L"animdata\\Penitent\\penitent_priedieu_bended_knee_with_aura.txt", true);

	m_pAnimator->SetAnimDuration(L"Praying", 0.05f);
	m_pAnimator->SetAnimDuration(L"Praying_L", 0.05f);

	// PrayAuraOff
	pTex = CAssetMgr::GetInst()->LoadTexture(L"PrayingAuraOff", L"texture\\Penitent\\penitent_priedieu_bended_knee_aura_turnoff.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"PrayingAuraOff_L", L"texture\\Penitent\\penitent_priedieu_bended_knee_aura_turnoff.png");


	m_pAnimator->LoadAnimation(pTex, L"PrayingAuraOff", L"animdata\\Penitent\\penitent_priedieu_bended_knee_aura_turnoff.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"PrayingAuraOff_L", L"animdata\\Penitent\\penitent_priedieu_bended_knee_aura_turnoff.txt", true);

	m_pAnimator->SetAnimDuration(L"PrayingAuraOff", 0.05f);
	m_pAnimator->SetAnimDuration(L"PrayingAuraOff_L", 0.05f);


	// PrayEnd

	pTex = CAssetMgr::GetInst()->LoadTexture(L"PrayEnd", L"texture\\Penitent\\penitent_priedieu_stand_up_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"PrayEnd_L", L"texture\\Penitent\\penitent_priedieu_stand_up_anim.png");


	m_pAnimator->LoadAnimation(pTex, L"PrayEnd", L"animdata\\Penitent\\penitent_priedieu_stand_up_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"PrayEnd_L", L"animdata\\Penitent\\penitent_priedieu_stand_up_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"PrayEnd", 0.05f);
	m_pAnimator->SetAnimDuration(L"PrayEnd_L", 0.05f);

	// FallingAhead
	pTex = CAssetMgr::GetInst()->LoadTexture(L"FallingAhead", L"texture\\Penitent\\penitent_falling_ahead_anim 1.png");
	m_pAnimator->LoadAnimation(L"animdata\\Penitent\\penitent_falling_ahead_anim.txt");

	// ======================
	//     이동 관련 State 
	// ======================

	// Run
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Run", L"texture\\Penitent\\penitent_running_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTexture(L"Run_L", L"texture\\Penitent\\penitent_running_anim_L.png");

	m_pAnimator->LoadAnimation(pTex, L"Run", L"animdata\\Penitent\\penitent_running_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Run_L", L"animdata\\Penitent\\penitent_running_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"Run", 0.04f);
	m_pAnimator->SetAnimDuration(L"Run_L", 0.04f);

	// Start_Run
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Start_Run", L"texture\\Penitent\\penintent_start_run_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Start_Run_L", L"texture\\Penitent\\penintent_start_run_anim.png");


	m_pAnimator->LoadAnimation(pTex, L"Start_Run", L"animdata\\Penitent\\penintent_start_run_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Start_Run_L", L"animdata\\Penitent\\penintent_start_run_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"Start_Run", 0.03f);
	m_pAnimator->SetAnimDuration(L"Start_Run_L", 0.03f);

	// Stop_Run

	pTex = CAssetMgr::GetInst()->LoadTexture(L"Stop_Run", L"texture\\Penitent\\penintent_stop_run_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Stop_Run_L", L"texture\\Penitent\\penintent_stop_run_anim.png");


	m_pAnimator->LoadAnimation(pTex, L"Stop_Run", L"animdata\\Penitent\\penintent_stop_run_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Stop_Run_L", L"animdata\\Penitent\\penintent_stop_run_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"Stop_Run", 0.06f);
	m_pAnimator->SetAnimDuration(L"Stop_Run_L", 0.06f);

	// penitent_crouch_anim
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Crouch", L"texture\\Penitent\\penitent_crouch_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Crouch_L", L"texture\\Penitent\\penitent_crouch_anim.png");

	m_pAnimator->LoadAnimation(pTex, L"Crouch", L"animdata\\Penitent\\penitent_crouch_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Crouch_L", L"animdata\\Penitent\\penitent_crouch_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"Crouch", 0.05f);
	m_pAnimator->SetAnimDuration(L"Crouch_L", 0.05f);

	//penitent_crouching_anim

	m_pAnimator->LoadAnimation(pTex, L"Crouching", L"animdata\\Penitent\\penitent_crouching_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Crouching_L", L"animdata\\Penitent\\penitent_crouching_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"Crouching", 0.1f);
	m_pAnimator->SetAnimDuration(L"Crouching_L", 0.1f);


	//penitent_crouch_up_anim
	pTex = CAssetMgr::GetInst()->LoadTexture(L"CrouchUp", L"texture\\Penitent\\penitent_crouch_up_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"CrouchUp_L", L"texture\\Penitent\\penitent_crouch_up_anim.png");

	m_pAnimator->LoadAnimation(pTex, L"CrouchUp", L"animdata\\Penitent\\penitent_crouch_up_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"CrouchUp_L", L"animdata\\Penitent\\penitent_crouch_up_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"CrouchUp", 0.06f);
	m_pAnimator->SetAnimDuration(L"CrouchUp_L", 0.06f);

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

	// JumpForward

	pTex = CAssetMgr::GetInst()->LoadTexture(L"JumpForward", L"texture\\Penitent\\penitent_jum_forward_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"JumpForward_L", L"texture\\Penitent\\penitent_jum_forward_anim.png");

	m_pAnimator->LoadAnimation(pTex, L"JumpForward", L"animdata\\Penitent\\penitent_jum_forward_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"JumpForward_L", L"animdata\\Penitent\\penitent_jum_forward_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"JumpForward", 0.08f);
	m_pAnimator->SetAnimDuration(L"JumpForward_L", 0.08f);

	// JumpForwardFall

	m_pAnimator->LoadAnimation(pTex, L"JumpForwardFall", L"animdata\\Penitent\\penitent_jum_forward_fall.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"JumpForwardFall_L", L"animdata\\Penitent\\penitent_jum_forward_fall.txt", true);

	m_pAnimator->SetAnimDuration(L"JumpForwardFall", 0.05f);
	m_pAnimator->SetAnimDuration(L"JumpForwardFall_L", 0.05f);

	// Dodge
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Dodge", L"texture\\Penitent\\penitent_dodge_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Dodge_L", L"texture\\Penitent\\penitent_dodge_anim.png");


	m_pAnimator->LoadAnimation(pTex, L"Dodge", L"animdata\\Penitent\\penitent_dodge_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Dodge_L", L"animdata\\Penitent\\penitent_dodge_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"Dodge", 0.04f);
	m_pAnimator->SetAnimDuration(L"Dodge_L", 0.04f);

	// penitent_start_to_run_from_dodge_anim
	pTex = CAssetMgr::GetInst()->LoadTexture(L"DodgeToRun", L"texture\\Penitent\\penitent_start_to_run_from_dodge_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"DodgeToRun_L", L"texture\\Penitent\\penitent_start_to_run_from_dodge_anim.png");


	m_pAnimator->LoadAnimation(pTex, L"DodgeToRun", L"animdata\\Penitent\\penitent_start_to_run_from_dodge_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"DodgeToRun_L", L"animdata\\Penitent\\penitent_start_to_run_from_dodge_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"DodgeToRun", 0.04f);
	m_pAnimator->SetAnimDuration(L"DodgeToRun_L", 0.04f);

	// Standing
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Standing", L"texture\\Penitent\\penintent_standing_up.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Standing_L", L"texture\\Penitent\\penintent_standing_up.png");


	m_pAnimator->LoadAnimation(pTex, L"Standing", L"animdata\\Penitent\\penintent_standing_up.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Standing_L", L"animdata\\Penitent\\penintent_standing_up.txt", true);

	m_pAnimator->SetAnimDuration(L"Standing", 0.04f);
	m_pAnimator->SetAnimDuration(L"Standing_L", 0.04f);

	// HangOn
	pTex = CAssetMgr::GetInst()->LoadTexture(L"HangOn", L"texture\\Penitent\\penitent_hangonledge_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"HangOn_L", L"texture\\Penitent\\penitent_hangonledge_anim.png");


	m_pAnimator->LoadAnimation(pTex, L"HangOn", L"animdata\\Penitent\\penitent_hangonledge_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"HangOn_L", L"animdata\\Penitent\\penitent_hangonledge_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"HangOn", 0.04f);
	m_pAnimator->SetAnimDuration(L"HangOn_L", 0.04f);


	// Climb
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Climb", L"texture\\Penitent\\penitent_climbledge_reviewed.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Climb_L", L"texture\\Penitent\\penitent_climbledge_reviewed.png");


	m_pAnimator->LoadAnimation(pTex, L"Climb", L"animdata\\Penitent\\penitent_climbledge_reviewed.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Climb_L", L"animdata\\Penitent\\penitent_climbledge_reviewed.txt", true);

	m_pAnimator->SetAnimDuration(L"Climb", 0.04f);
	m_pAnimator->SetAnimDuration(L"Climb_L", 0.04f);

	//penitent_ladder_down_from_ground_anim
	pTex = CAssetMgr::GetInst()->LoadTexture(L"LadderDown", L"texture\\Penitent\\penitent_ladder_down_from_ground_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"LadderDown_L", L"texture\\Penitent\\penitent_ladder_down_from_ground_anim.png");


	m_pAnimator->LoadAnimation(pTex, L"LadderDown", L"animdata\\Penitent\\penitent_ladder_down_from_ground_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"LadderDown_L", L"animdata\\Penitent\\penitent_ladder_down_from_ground_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"LadderDown", 0.04f);
	m_pAnimator->SetAnimDuration(L"LadderDown_L", 0.04f);

	//penintent_ladder_up_from_ground
	pTex = CAssetMgr::GetInst()->LoadTexture(L"LadderUp", L"texture\\Penitent\\penitent_ladder_down_from_ground_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"LadderUp_L", L"texture\\Penitent\\penitent_ladder_down_from_ground_anim.png");

	
	m_pAnimator->LoadAnimation(pTex, L"LadderUp", L"animdata\\Penitent\\penintent_ladder_up_from_ground.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"LadderUp_L", L"animdata\\Penitent\\penintent_ladder_up_from_ground.txt", true);

	m_pAnimator->SetAnimDuration(L"LadderUp", 0.04f);
	m_pAnimator->SetAnimDuration(L"LadderUp_L", 0.04f);

	//penintent_ladder_climb_loop_anim
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Ladder", L"texture\\Penitent\\penintent_ladder_climb_loop_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Ladder_L", L"texture\\Penitent\\penintent_ladder_climb_loop_anim.png");


	m_pAnimator->LoadAnimation(pTex, L"Ladder", L"animdata\\Penitent\\penintent_ladder_climb_loop_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Ladder_L", L"animdata\\Penitent\\penintent_ladder_climb_loop_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"Ladder", 0.04f);
	m_pAnimator->SetAnimDuration(L"Ladder_L", 0.04f);




	// ================
	//   Attck State
	// ================

	// Attack
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Attack", L"texture\\Penitent\\penitent_three_hits_attack_combo_no_slashes.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Attack_L", L"texture\\Penitent\\penitent_three_hits_attack_combo_no_slashes.png");

	m_pAnimator->LoadAnimation(pTex, L"Attack", L"animdata\\Penitent\\penitent_three_hits_attack_combo_no_slashes.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Attack_L", L"animdata\\Penitent\\penitent_three_hits_attack_combo_no_slashes.txt", true);

	m_pAnimator->SetAnimDuration(L"Attack", 0.05f);
	m_pAnimator->SetAnimDuration(L"Attack_L", 0.05f);

	//UpwardAttck
	pTex = CAssetMgr::GetInst()->LoadTexture(L"UpwardAttck", L"texture\\Penitent\\penitent_upward_attack_clamped_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"UpwardAttck_L", L"texture\\Penitent\\penitent_upward_attack_clamped_anim.png");

	m_pAnimator->LoadAnimation(pTex, L"UpwardAttck", L"animdata\\Penitent\\penitent_upward_attack_clamped_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"UpwardAttck_L", L"animdata\\Penitent\\penitent_upward_attack_clamped_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"UpwardAttck", 0.03f);
	m_pAnimator->SetAnimDuration(L"UpwardAttck_L", 0.03f);

	//penitent_crouchslash_noslashes_anim
	pTex = CAssetMgr::GetInst()->LoadTexture(L"CrouchATT", L"texture\\Penitent\\penitent_crouchslash_noslashes_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"CrouchATT_L", L"texture\\Penitent\\penitent_crouchslash_noslashes_anim.png");

	m_pAnimator->LoadAnimation(pTex, L"CrouchATT", L"animdata\\Penitent\\penitent_crouchslash_noslashes_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"CrouchATT_L", L"animdata\\Penitent\\penitent_crouchslash_noslashes_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"CrouchATT", 0.04f);
	m_pAnimator->SetAnimDuration(L"CrouchATT_L", 0.04f);

	// JumpATT
	pTex = CAssetMgr::GetInst()->LoadTexture(L"JumpATT", L"texture\\Penitent\\penitent_jumping_attack_noslashes.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"JumpATT_L", L"texture\\Penitent\\penitent_jumping_attack_noslashes.png");


	m_pAnimator->LoadAnimation(pTex, L"JumpATT", L"animdata\\Penitent\\penitent_jumping_attack_noslashes.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"JumpATT_L", L"animdata\\Penitent\\penitent_jumping_attack_noslashes.txt", true);

	m_pAnimator->SetAnimDuration(L"JumpATT", 0.06f);
	m_pAnimator->SetAnimDuration(L"JumpATT_L", 0.06f);

	//UpwardAttck_Jump
	pTex = CAssetMgr::GetInst()->LoadTexture(L"UpwardAttck_Jump", L"texture\\Penitent\\penitent_upward_attack_jump.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"UpwardAttck_Jump_L", L"texture\\Penitent\\penitent_upward_attack_jump.png");

	m_pAnimator->LoadAnimation(pTex, L"UpwardAttck_Jump", L"animdata\\Penitent\\penitent_upward_attack_jump.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"UpwardAttck_Jump_L", L"animdata\\Penitent\\penitent_upward_attack_jump.txt", true);

	m_pAnimator->SetAnimDuration(L"UpwardAttck_Jump", 0.03f);
	m_pAnimator->SetAnimDuration(L"UpwardAttck_Jump_L", 0.03f);

	// penitent_charged_attack_v2_anim
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Charging", L"texture\\Penitent\\penitent_charged_attack_v2_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"Charging_L", L"texture\\Penitent\\penitent_charged_attack_v2_anim.png");

	m_pAnimator->LoadAnimation(pTex, L"Charging", L"animdata\\Penitent\\penitent_charged_attack_v2_anim.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Charging_L", L"animdata\\Penitent\\penitent_charged_attack_v2_anim.txt", true);

	m_pAnimator->SetAnimDuration(L"Charging", 0.04f);
	m_pAnimator->SetAnimDuration(L"Charging_L", 0.04f);


}

void CPenitent::EffectInit()
{

	// three_hits_attack_slashes_lvl1_anim
	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"AttackSlash", L"texture\\Penitent\\three_hits_attack_slashes_lvl1_anim.png");
	CTexture* pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"AttackSlash_L", L"texture\\Penitent\\three_hits_attack_slashes_lvl1_anim.png");

	m_pEffector->LoadAnimation(pTex, L"AttackSlash", L"animdata\\Penitent\\three_hits_attack_slashes_lvl1_anim.txt");
	m_pEffector->LoadAnimation(pTexReverse, L"AttackSlash_L", L"animdata\\Penitent\\three_hits_attack_slashes_lvl1_anim.txt", true);

	m_pEffector->SetAnimDuration(L"AttackSlash", 0.05f);
	m_pEffector->SetAnimDuration(L"AttackSlash_L", 0.05f);


	// UpwardATT
	pTex = CAssetMgr::GetInst()->LoadTexture(L"UpwardATT", L"texture\\Penitent\\penitent_upward_attack_slash_lvl1.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"UpwardATT_L", L"texture\\Penitent\\penitent_upward_attack_slash_lvl1.png");

	m_pEffector->LoadAnimation(pTex, L"UpwardATT", L"animdata\\Penitent\\penitent_upward_attack_slash_lvl1.txt");
	m_pEffector->LoadAnimation(pTexReverse, L"UpwardATT_L", L"animdata\\Penitent\\penitent_upward_attack_slash_lvl1.txt", true);

	m_pEffector->SetAnimDuration(L"UpwardATT", 0.03f);
	m_pEffector->SetAnimDuration(L"UpwardATT_L", 0.03f);

	// UpwardATTJump
	pTex = CAssetMgr::GetInst()->LoadTexture(L"UpwardATTJump", L"texture\\Penitent\\penitent_upward_attack_slash_lvl1_jump.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"UpwardATTJump_L", L"texture\\Penitent\\penitent_upward_attack_slash_lvl1_jump.png");

	m_pEffector->LoadAnimation(pTex, L"UpwardATTJump", L"animdata\\Penitent\\penitent_upward_attack_slash_lvl1_jump.txt");
	m_pEffector->LoadAnimation(pTexReverse, L"UpwardATTJump_L", L"animdata\\Penitent\\penitent_upward_attack_slash_lvl1_jump.txt", true);

	m_pEffector->SetAnimDuration(L"UpwardATTJump", 0.03f);
	m_pEffector->SetAnimDuration(L"UpwardATTJump_L", 0.03f);

	// JumpATTSlash1
	pTex = CAssetMgr::GetInst()->LoadTexture(L"JumpATTSlash1", L"texture\\Penitent\\penitent_jumping_attack_slasheslvl1.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"JumpATTSlash1_L", L"texture\\Penitent\\penitent_jumping_attack_slasheslvl1.png");

	m_pEffector->LoadAnimation(pTex, L"JumpATTSlash1", L"animdata\\Penitent\\penitent_jumping_attack_slasheslvl1.txt");
	m_pEffector->LoadAnimation(pTexReverse, L"JumpATTSlash1_L", L"animdata\\Penitent\\penitent_jumping_attack_slasheslvl1.txt", true);

	m_pEffector->SetAnimDuration(L"JumpATTSlash1", 0.06f);
	m_pEffector->SetAnimDuration(L"JumpATTSlash1_L", 0.06f);

	// JumpATTSlash2
	m_pEffector->LoadAnimation(pTex, L"JumpATTSlash2", L"animdata\\Penitent\\penitent_jumping_attack_slasheslvl2.txt");
	m_pEffector->LoadAnimation(pTexReverse, L"JumpATTSlash2_L", L"animdata\\Penitent\\penitent_jumping_attack_slasheslvl2.txt", true);

	m_pEffector->SetAnimDuration(L"JumpATTSlash2", 0.06f);
	m_pEffector->SetAnimDuration(L"JumpATTSlash2_L", 0.06f);

	// penitent_crouch_slashes_anim
	pTex = CAssetMgr::GetInst()->LoadTexture(L"CrouchAttackSlash", L"texture\\Penitent\\penitent_crouch_slashes_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"CrouchAttackSlash_L", L"texture\\Penitent\\penitent_crouch_slashes_anim.png");

	m_pEffector->LoadAnimation(pTex, L"CrouchAttackSlash", L"animdata\\Penitent\\penitent_crouch_slashes_anim.txt");
	m_pEffector->LoadAnimation(pTexReverse, L"CrouchAttackSlash_L", L"animdata\\Penitent\\penitent_crouch_slashes_anim.txt", true);

	m_pEffector->SetAnimDuration(L"CrouchAttackSlash", 0.04f);
	m_pEffector->SetAnimDuration(L"CrouchAttackSlash_L", 0.04f);




		
	// None
	m_pEffector->CreateAnimation(L"None", pTex, Vec2(0.f, 0.f), Vec2(0.f, 0.f), Vec2(0.f, 0.f), 0.1f, 1);

	//m_pEffector->Play(L"AttackSlash", true);
}

void CPenitent::DustAnimInit()
{
	// penitent_running_dust_anim
	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"RunDust", L"texture\\Penitent\\penitent_running_dust_anim.png");
	CTexture* pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"RunDust_L", L"texture\\Penitent\\penitent_running_dust_anim.png");

	m_pDustAnimator->LoadAnimation(pTex, L"RunDust", L"animdata\\Penitent\\penitent_running_dust_anim.txt");
	m_pDustAnimator->LoadAnimation(pTexReverse, L"RunDust_L", L"animdata\\Penitent\\penitent_running_dust_anim.txt", true);

	m_pDustAnimator->SetAnimDuration(L"RunDust", 0.08f);
	m_pDustAnimator->SetAnimDuration(L"RunDust_L", 0.08f);


	// penitent_stop_dodge_dust_anim
	pTex = CAssetMgr::GetInst()->LoadTexture(L"StopDodge", L"texture\\Penitent\\penitent_stop_dodge_dust_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"StopDodge_L", L"texture\\Penitent\\penitent_stop_dodge_dust_anim.png");

	m_pDustAnimator->LoadAnimation(pTex, L"StopDodge", L"animdata\\Penitent\\penitent_stop_dodge_dust_anim.txt");
	m_pDustAnimator->LoadAnimation(pTexReverse, L"StopDodge_L", L"animdata\\Penitent\\penitent_stop_dodge_dust_anim.txt", true);

	m_pDustAnimator->SetAnimDuration(L"StopDodge", 0.08f);
	m_pDustAnimator->SetAnimDuration(L"StopDodge_L", 0.08f);

	// penitent_start_dodge_dust_anim
	pTex = CAssetMgr::GetInst()->LoadTexture(L"StartDodge", L"texture\\Penitent\\penitent_start_dodge_dust_anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"StartDodge_L", L"texture\\Penitent\\penitent_start_dodge_dust_anim.png");

	m_pDustAnimator->LoadAnimation(pTex, L"StartDodge", L"animdata\\Penitent\\penitent_start_dodge_dust_anim.txt");
	m_pDustAnimator->LoadAnimation(pTexReverse, L"StartDodge_L", L"animdata\\Penitent\\penitent_start_dodge_dust_anim.txt", true);

	m_pDustAnimator->SetAnimDuration(L"StartDodge", 0.08f);
	m_pDustAnimator->SetAnimDuration(L"StartDodge_L", 0.08f);

	// penitent-stop-running-dust
	pTex = CAssetMgr::GetInst()->LoadTexture(L"StopRun", L"texture\\Penitent\\penitent-stop-running-dust.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"StopRun_L", L"texture\\Penitent\\penitent-stop-running-dust.png");

	m_pDustAnimator->LoadAnimation(pTex, L"StopRun", L"animdata\\Penitent\\penitent-stop-running-dust.txt");
	m_pDustAnimator->LoadAnimation(pTexReverse, L"StopRun_L", L"animdata\\Penitent\\penitent-stop-running-dust.txt", true);

	m_pDustAnimator->SetAnimDuration(L"StopRun", 0.08f);
	m_pDustAnimator->SetAnimDuration(L"StopRun_L", 0.08f);


	// penitent-landing-dust-anim
	pTex = CAssetMgr::GetInst()->LoadTexture(L"StandingDust", L"texture\\Penitent\\penitent-jumping-landing-dust-anim.png");
	pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"StandingDust_L", L"texture\\Penitent\\penitent-jumping-landing-dust-anim.png");

	m_pDustAnimator->LoadAnimation(pTex, L"StandingDust", L"animdata\\Penitent\\penitent-jumping-landing-dust-anim.txt");
	m_pDustAnimator->LoadAnimation(pTexReverse, L"StandingDust_L", L"animdata\\Penitent\\penitent-jumping-landing-dust-anim.txt", true);

	m_pDustAnimator->SetAnimDuration(L"StandingDust", 0.07f);
	m_pDustAnimator->SetAnimDuration(L"StandingDust_L", 0.07f);

	// penitent_jumping_dust_anim
	m_pDustAnimator->LoadAnimation(pTex, L"Jumping_dust", L"animdata\\Penitent\\penitent_jumping_dust_anim.txt");
	m_pDustAnimator->LoadAnimation(pTexReverse, L"Jumping_dust_L", L"animdata\\Penitent\\penitent_jumping_dust_anim.txt", true);

	m_pDustAnimator->SetAnimDuration(L"Jumping_dust", 0.08f);
	m_pDustAnimator->SetAnimDuration(L"Jumping_dust_L", 0.08f);




	//m_pDustAnimator->Play(L"Jumping_dust", true);



}

void CPenitent::StateInit()
{
	m_pSM->AddState((UINT)PENITENT_STATE::FALLINGAHEAD, new CPenitentFallingAhead);
	m_pSM->AddState((UINT)PENITENT_STATE::RISING, new CPenitentRising);
	m_pSM->AddState((UINT)PENITENT_STATE::IDLE, new CPenitentIdle);
	m_pSM->AddState((UINT)PENITENT_STATE::STARTRRUN, new CPenitentStartRun);
	m_pSM->AddState((UINT)PENITENT_STATE::RUN, new CPenitentRun);
	m_pSM->AddState((UINT)PENITENT_STATE::STOPRUN, new CPenitentStopRun);
	m_pSM->AddState((UINT)PENITENT_STATE::JUMP, new CPenitentJump);
	m_pSM->AddState((UINT)PENITENT_STATE::FALL, new CPenitentFall);
	m_pSM->AddState((UINT)PENITENT_STATE::JUMPFORWARD, new CPenitentJumpForward);
	m_pSM->AddState((UINT)PENITENT_STATE::FALLFORWARD, new CPenitentFowardFall);
	m_pSM->AddState((UINT)PENITENT_STATE::ATTACK, new CPenitentAttack);
	m_pSM->AddState((UINT)PENITENT_STATE::UPWARDATTACK, new CPenitentUpwardATT);
	m_pSM->AddState((UINT)PENITENT_STATE::UPWARDATTACKJUMP, new CPenitentUpwardATTJump);
	m_pSM->AddState((UINT)PENITENT_STATE::DODGE, new CPenitentDodge);
	m_pSM->AddState((UINT)PENITENT_STATE::DODGETORUN, new CPenitentDodgeToRun);
	m_pSM->AddState((UINT)PENITENT_STATE::JUMPATT, new CPenitentJumpAttack);
	m_pSM->AddState((UINT)PENITENT_STATE::HEALTHPOTION, new CPenitentHealthPotion);
	m_pSM->AddState((UINT)PENITENT_STATE::CROUCH, new CPenitentCrouch);
	m_pSM->AddState((UINT)PENITENT_STATE::CROUCHING, new CPenitentCrouching);
	m_pSM->AddState((UINT)PENITENT_STATE::CROUCHUP, new CPenitentCrouchUp);
	m_pSM->AddState((UINT)PENITENT_STATE::CROUCHATT, new CPenitentCrouchATT);
	m_pSM->AddState((UINT)PENITENT_STATE::DEATH, new CPenitentDeath);
	m_pSM->AddState((UINT)PENITENT_STATE::NONE, new CPenitentNone);
	m_pSM->AddState((UINT)PENITENT_STATE::PRAYSTART, new CPenitentPrayStart);
	m_pSM->AddState((UINT)PENITENT_STATE::PRAYING, new CPenitentPraying);
	m_pSM->AddState((UINT)PENITENT_STATE::PRAYAURAOFF, new CPenitentPrayAuraOff);
	m_pSM->AddState((UINT)PENITENT_STATE::PRAYEND, new CPenitentPrayEnd);
	m_pSM->AddState((UINT)PENITENT_STATE::STANDING, new CPenitentStanding);
	m_pSM->AddState((UINT)PENITENT_STATE::CHARGING, new CPenitentCharging);
	m_pSM->AddState((UINT)PENITENT_STATE::CLIMB, new CPenitentClimb);
	m_pSM->AddState((UINT)PENITENT_STATE::HANGON, new CPenitentHangOn);
	m_pSM->AddState((UINT)PENITENT_STATE::LADDERDOWN, new CPenitentLadderDown);
	m_pSM->AddState((UINT)PENITENT_STATE::LADDER, new CPenitentLadder);
	m_pSM->AddState((UINT)PENITENT_STATE::LADDERUP, new CPenitentLadderUp);
	m_pSM->AddState((UINT)PENITENT_STATE::PUSHBACK, new CPenitentPushBack);


	m_pSM->SetGlobalState((UINT)PENITENT_STATE::DEATH);
}


