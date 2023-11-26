#include "pch.h"
#include "CStage01_4.h"

#include "CEngine.h"

#include "CAssetMgr.h"

#include "CBackground.h"

#include "CPenitent.h"
#include "CPlatform.h"
#include "CPenitentUI.h"
#include "CTearsUI.h"

#include "CElderBrother.h"

#include "CRayBeam.h"
#include "CSpawner.h"
#include "CWall.h"

#include "CKeyMgr.h"

#include "CBossPanel.h"
#include "CBossHP.h"

#include "CLevelMgr.h"
#include "CPenitent.h"

#include "CBossIntro.h"

#include "CElderShadow.h"

void CStage01_4::BossIntro()
{
	// Penitent State 변경
	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();
	CStateMachine* pSM = pPenitent->GetComponent<CStateMachine>();
	pSM->ChangeState((UINT)PENITENT_STATE::INTRO);
	
	// Camera 설정
	//CCamera::GetInst()->SetTarget(nullptr);
	//CCamera::GetInst()->SetSpeed(200.f);
	//CCamera::GetInst()->SetLookAt(Vec2(1430.f,820.f));
	//CCamera::GetInst()->SetLookAtOffsetY(0.f);

	// 벽 설정
	m_pLeftWall->SetPos(Vec2(355.f, 870.f));
	m_pRightWall->SetPos(Vec2(2405.f, 870.f));


	// ElderBrother shadow Animation 재생
	CStateMachine* p_AI = m_pShadow->GetComponent<CStateMachine>();
	p_AI->ChangeState((UINT)ELDERBROTHER::ATTACK);


}

void CStage01_4::IntroEnd()
{
	// Camera Limit 
	CCamera::GetInst()->SetCameraLimitLT(Vec2(200.f * 2.f, 255.f * 2.f));
	CCamera::GetInst()->SetCameraLimit(Vec2(1180.f * 2.f, 615.f * 2.f));
	
	// BGM 변경
	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"Final Boss_MASTER", L"sound\\BGM\\Final Boss_MASTER.wav");
	pSound->PlayToBGM();

	// Penitent State 변경
	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();
	CStateMachine* pSM = pPenitent->GetComponent<CStateMachine>();
	pSM->ChangeState((UINT)PENITENT_STATE::IDLE);

	// Boss HP UI 표시
	const vector<CObj*> vecUI = CLevelMgr::GetInst()->GetCurLevel()->GetObjects(LAYER::UI);
	for (int i = 0; i < vecUI.size(); ++i)
	{
		if (vecUI[i]->GetName() == L"BossPanel")
		{
			CBossPanel* pPanel = dynamic_cast<CBossPanel*>(vecUI[i]);
			pPanel->On();
		}
	}

	// Boss State 변경
	CObj* pBoss = GetBoss();
	pSM = pBoss->GetComponent<CStateMachine>();
	pSM->ChangeState((UINT)ELDERBROTHER::INTROJUMP);
}

// 보스가 죽었을 때
void CStage01_4::BossDeath()
{
	// Boss UI Off
	const vector<CObj*> vecUI = CLevelMgr::GetInst()->GetCurLevel()->GetObjects(LAYER::UI);
	for (int i = 0; i < vecUI.size(); ++i)
	{
		if (vecUI[i]->GetName() == L"BossPanel")
		{
			CBossPanel* pPanel = dynamic_cast<CBossPanel*>(vecUI[i]);
			pPanel->Off();
		}
	}

	// BGM 변경
	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"Boss_Fight_Ending", L"sound\\KeyEvents\\Boss_Fight_Ending.wav");
	pSound->PlayToBGM();

	// Boss Clear Screen
	CCamera::GetInst()->BossClear(1.f);

	// 벽 설정
	m_pLeftWall->Destroy();
	m_pRightWall->Destroy();

	// Camera
	CCamera::GetInst()->SetCameraLimitLT(Vec2(100.f * 2.f, 255.f * 2.f));
	CCamera::GetInst()->SetCameraLimit(Vec2(1380.f * 2.f, 615.f * 2.f));

}

void CStage01_4::init()
{
	// Background 0
	CBackground* pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_4_BeforeParallax_0", L"texture\\Map\\Brotherhood\\1-4\\1_4_BeforeParallax_0.png"));
	pBackGround->SetParallaxSpeed(Vec2(0.1f, 0.3f));
	pBackGround->SetPos(Vec2(0.f, 0.f));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::BACKGROUND, pBackGround);

	// Background 1
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_4_BeforeParallax_1", L"texture\\Map\\Brotherhood\\1-4\\1_4_BeforeParallax_1.png"));
	pBackGround->SetParallaxSpeed(Vec2(0.2f, 0.3f));
	pBackGround->SetPos(Vec2(-600.f, -500.f));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::BACKGROUND, pBackGround);

	// Background 2
	//pBackGround = new CBackground;
	//pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_4_BeforeParallax_2", L"texture\\Map\\Brotherhood\\1-4\\1_4_BeforeParallax_2.png"));
	//pBackGround->SetParallaxSpeed(Vec2(0.5f, 0.3f));
	//pBackGround->SetPos(Vec2(0.f, -450.f));
	//pBackGround->SetScale(Vec2(2.f, 2.f));
	//AddObject(LAYER::BACKGROUND, pBackGround);

	// Background 3
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_4_BeforeParallax_3", L"texture\\Map\\Brotherhood\\1-4\\1_4_BeforeParallax_3.png"));
	pBackGround->SetParallaxSpeed(Vec2(0.7f, 0.3f));
	pBackGround->SetPos(Vec2(0.f, 80.f));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::BACKGROUND, pBackGround);


	CElderShadow* pShadow = new CElderShadow;
	pShadow->SetPos(Vec2(1770.f, 1000.f));
	pShadow->SetScale(Vec2(1.5f, 1.5f));
	pShadow->SetDir(false);
	AddObject(LAYER::BACKGROUND, pShadow);

	m_pShadow = pShadow;



	// Background 4
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_4_BeforeParallax_4", L"texture\\Map\\Brotherhood\\1-4\\1_4_BeforeParallax_4.png"));
	pBackGround->SetParallaxSpeed(Vec2(0.8f, 0.3f));
	pBackGround->SetPos(Vec2(-100.f, 100.f));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::BACKGROUND, pBackGround);


	// Tile 
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_4_Tile", L"texture\\Map\\Brotherhood\\1-4\\1_4_Tile.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::TILE, pBackGround);

	// Foreground 1
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_4_Door", L"texture\\Map\\Brotherhood\\1-4\\1_4_Door.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::FOREGROUND, pBackGround);

	// Foreground 2
	//pBackGround = new CBackground;
	//pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_4_AfterLayer_0", L"texture\\Map\\Brotherhood\\1-4\\1_4_AfterLayer_0.png"));
	//pBackGround->SetScale(Vec2(2.f, 2.f));
	//AddObject(LAYER::FOREGROUND, pBackGround);

	CPlatform* pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(524.f, 1126.f));
	pPlatform->SetScale(Vec2(930.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(1080.f, 1100.f));
	pPlatform->SetScale(Vec2(300.f, 50.f));
	pPlatform->SetAngle(-15.f);
	AddObject(LAYER::PLATFORM, pPlatform);

	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(1470.f, 1068.f));
	pPlatform->SetScale(Vec2(500.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);


	CElderBrother* pElder = new CElderBrother;
	pElder->SetPos(Vec2(1570.f, 260.f));
	pElder->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::MONSTER, pElder);


	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(1860.f, 1095.f));
	pPlatform->SetScale(Vec2(300.f, 50.f));
	pPlatform->SetAngle(15.f);
	AddObject(LAYER::PLATFORM, pPlatform);

	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(2450.f, 1130.f));
	pPlatform->SetScale(Vec2(950.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	CSpawner* pSpawner = new CSpawner;
	pSpawner->Off();
	AddObject(LAYER::SPAWNER, pSpawner);

	CRayBeam* pRay = new CRayBeam;
	pRay->SetScale(Vec2(2.f, 2.f));
	pSpawner->AddRay(pRay);
	AddObject(LAYER::MONSTER_PJ, pRay);

	pRay = new CRayBeam;
	pRay->SetScale(Vec2(2.f, 2.f));
	pSpawner->AddRay(pRay);
	AddObject(LAYER::MONSTER_PJ, pRay);

	pRay = new CRayBeam;
	pRay->SetScale(Vec2(2.f, 2.f));
	pSpawner->AddRay(pRay);
	AddObject(LAYER::MONSTER_PJ, pRay);

	pRay = new CRayBeam;
	pRay->SetScale(Vec2(2.f, 2.f));
	pSpawner->AddRay(pRay);
	AddObject(LAYER::MONSTER_PJ, pRay);

	pRay = new CRayBeam;
	pRay->SetScale(Vec2(2.f, 2.f));
	pSpawner->AddRay(pRay);
	AddObject(LAYER::MONSTER_PJ, pRay);

	pRay = new CRayBeam;
	pRay->SetScale(Vec2(2.f, 2.f));
	pSpawner->AddRay(pRay);
	AddObject(LAYER::MONSTER_PJ, pRay);

	pRay = new CRayBeam;
	pRay->SetScale(Vec2(2.f, 2.f));
	pSpawner->AddRay(pRay);
	AddObject(LAYER::MONSTER_PJ, pRay);

	
	RegisterBoss(pElder);




	// UI 생성
	CPenitentUI* pPenitentUI = new CPenitentUI;
	AddObject(LAYER::UI, pPenitentUI);

	CTearsUI* pTearsUI = new CTearsUI;
	AddObject(LAYER::UI, pTearsUI);

	CBossPanel* pBossPanel = new CBossPanel;
	AddObject(LAYER::UI, pBossPanel);

	pBossPanel->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"ElderBrotherName", L"texture\\UI\\ElderBrotherName.png"));


	// wall 
	m_pLeftWall = new CWall;
	
	m_pLeftWall->SetPos(Vec2(0.f, 0.f));
	m_pLeftWall->SetScale(Vec2(50.f, 500.f));
	AddObject(LAYER::PLATFORM, m_pLeftWall);

	m_pRightWall = new CWall;

	m_pRightWall->SetPos(Vec2(0.f, 0.f));
	m_pRightWall->SetScale(Vec2(50.f, 500.f));
	AddObject(LAYER::PLATFORM, m_pRightWall);


	// Boss Intro 
	CBossIntro* pBossIntro = new CBossIntro;
	pBossIntro->SetPos(Vec2(1320.f, 968.f));
	AddObject(LAYER::BOSSINTRO, pBossIntro);


}

void CStage01_4::enter()
{
	//Penitent 생성
	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();
	pPenitent->SetState(PENITENT_STATE::IDLE);
	pPenitent->SetPos(Vec2(232.f, 1126.f));
	pPenitent->SetLeft(false);
	if ((UINT)LEVEL_TYPE::STAGE01_3 == CLevelMgr::GetInst()->GetPrevLevel())
	{
		pPenitent->SetState(PENITENT_STATE::IDLE);
		pPenitent->SetPos(Vec2(232.f, 1126.f));
	}

	if ((UINT)LEVEL_TYPE::STAGE01_5 == CLevelMgr::GetInst()->GetPrevLevel())
	{
		pPenitent->SetState(PENITENT_STATE::IDLE);
		pPenitent->SetPos(Vec2(2740.f, 1126.f));
	}
	AddObject(LAYER::PLAYER, pPenitent);

	// 카메라 설정
	CCamera::GetInst()->FadeIn(1.f);
	CCamera::GetInst()->InitLookAt(pPenitent->GetPos());
	CCamera::GetInst()->SetTarget(pPenitent);
	CCamera::GetInst()->SetLookAtOffsetY(-230.f);
	CCamera::GetInst()->SetCameraLimitLT(Vec2(100.f * 2.f, 255.f * 2.f));
	CCamera::GetInst()->SetCameraLimit(Vec2(1380.f * 2.f, 615.f * 2.f));

	// BGM 변경
	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"Boss_Zone_Background", L"sound\\BGM\\Boss_Zone_Background.wav");
	pSound->PlayToBGM();

}

void CStage01_4::exit()
{
	PullOutObject(LAYER::PLAYER);
}

void CStage01_4::tick()
{
	CLevel::tick();

	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();

	if (pPenitent->GetPos().x < 100.f * 2 && !pPenitent->GetIsLeft())
	{
		CCamera::GetInst()->FixLookAt();
		pPenitent->SetLeft(true);
		pPenitent->SetState(PENITENT_STATE::NONE);

		CCamera::GetInst()->FadeOut(0.5f, LEVEL_TYPE::STAGE01_3);
	}

	if (pPenitent->GetPos().x > 1380.f * 2 && !pPenitent->GetIsLeft())
	{
		CCamera::GetInst()->FixLookAt();
		pPenitent->SetLeft(true);
		pPenitent->SetState(PENITENT_STATE::NONE);

		CCamera::GetInst()->FadeOut(0.5f, LEVEL_TYPE::STAGE01_5);
	}


}
