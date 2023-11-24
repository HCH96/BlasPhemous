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

#include "CKeyMgr.h"

#include "CBossPanel.h"
#include "CBossHP.h"


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

	// Background 4
	//pBackGround = new CBackground;
	//pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_4_BeforeParallax_4", L"texture\\Map\\Brotherhood\\1-4\\1_4_BeforeParallax_4.png"));
	//pBackGround->SetParallaxSpeed(Vec2(0.8f, 0.3f));
	//pBackGround->SetPos(Vec2(-100.f, 100.f));
	//pBackGround->SetScale(Vec2(2.f, 2.f));
	//AddObject(LAYER::BACKGROUND, pBackGround);


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
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_4_AfterLayer_0", L"texture\\Map\\Brotherhood\\1-4\\1_4_AfterLayer_0.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::FOREGROUND, pBackGround);

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
	pElder->SetPos(Vec2(1470.f, 1060.f));
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




	// UI ����
	CPenitentUI* pPenitentUI = new CPenitentUI;
	AddObject(LAYER::UI, pPenitentUI);

	CTearsUI* pTearsUI = new CTearsUI;
	AddObject(LAYER::UI, pTearsUI);

	CBossPanel* pBossPanel = new CBossPanel;
	AddObject(LAYER::UI, pBossPanel);



}

void CStage01_4::enter()
{
	//Penitent ����
	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();
	pPenitent->SetState(PENITENT_STATE::IDLE);
	pPenitent->SetPos(Vec2(232.f, 1100.f));
	pPenitent->SetLeft(false);
	if ((UINT)LEVEL_TYPE::STAGE01_3 == CLevelMgr::GetInst()->GetPrevLevel())
	{
		pPenitent->SetPos(Vec2(232.f, 1100.f));
	}

	if ((UINT)LEVEL_TYPE::STAGE01_5 == CLevelMgr::GetInst()->GetPrevLevel())
	{
		pPenitent->SetPos(Vec2(2740.f, 1100.f));
	}
	AddObject(LAYER::PLAYER, pPenitent);

	// ī�޶� ����
	CCamera::GetInst()->FadeIn(1.f);
	CCamera::GetInst()->InitLookAt(pPenitent->GetPos());
	CCamera::GetInst()->SetTarget(pPenitent);
	CCamera::GetInst()->SetLookAtOffsetY(-230.f);
	CCamera::GetInst()->SetCameraLimitLT(Vec2(100.f * 2.f, 255.f * 2.f));
	CCamera::GetInst()->SetCameraLimit(Vec2(1380.f * 2.f, 615.f * 2.f));

	// Sound
	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"Final Boss_MASTER", L"sound\\BGM\\Final Boss_MASTER.wav");
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
