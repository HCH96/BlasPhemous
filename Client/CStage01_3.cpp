#include "pch.h"
#include "CStage01_3.h"

#include "CEngine.h"

#include "CAssetMgr.h"

#include "CBackground.h"

#include "CPenitent.h"
#include "CPlatform.h"
#include "CPenitentUI.h"
#include "CTearsUI.h"
#include "CTexObj.h"
#include "CPriedieu.h"

void CStage01_3::init()
{
	// Background 0
	CBackground* pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_3_BeforeParallax_0", L"texture\\Map\\Brotherhood\\1-3\\1_3_BeforeParallax_0.png"));
	pBackGround->SetParallaxSpeed(Vec2(0.1f, 0.3f));
	pBackGround->SetPos(Vec2(0.f, 150.f));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::BACKGROUND, pBackGround);

	// Background 1
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_3_BeforeParallax_1", L"texture\\Map\\Brotherhood\\1-3\\1_3_BeforeParallax_1.png"));
	pBackGround->SetParallaxSpeed(Vec2(0.2f, 0.3f));
	pBackGround->SetPos(Vec2(-400.f, -230.f));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::BACKGROUND, pBackGround);

	// Background 2
	//pBackGround = new CBackground;
	//pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_3_BeforeParallax_2", L"texture\\Map\\Brotherhood\\1-3\\1_3_BeforeParallax_2.png"));
	//pBackGround->SetParallaxSpeed(Vec2(0.3f, 0.3f));
	//pBackGround->SetPos(Vec2(-700.f, -330.f));
	//pBackGround->SetScale(Vec2(2.f, 2.f));
	//AddObject(LAYER::BACKGROUND, pBackGround);

	// Background 3
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_3_BeforeParallax_3", L"texture\\Map\\Brotherhood\\1-3\\1_3_BeforeParallax_3.png"));
	pBackGround->SetParallaxSpeed(Vec2(0.4f, 0.3f));
	pBackGround->SetPos(Vec2(-500.f, -350.f));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::BACKGROUND, pBackGround);

	// Background 4
	//pBackGround = new CBackground;
	//pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_3_BeforeParallax_4", L"texture\\Map\\Brotherhood\\1-3\\1_3_BeforeParallax_4.png"));
	//pBackGround->SetParallaxSpeed(Vec2(0.5f, 0.3f));
	//pBackGround->SetPos(Vec2(-500.f, -350.f));
	//pBackGround->SetScale(Vec2(2.f, 2.f));
	//AddObject(LAYER::BACKGROUND, pBackGround);


	// Tile 
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_3_Tile", L"texture\\Map\\Brotherhood\\1-3\\1_3_Tile.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::TILE, pBackGround);

	// Foreground 1
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_3_Door", L"texture\\Map\\Brotherhood\\1-3\\1_3_Door.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::FOREGROUND, pBackGround);

	// Foreground 2
	//pBackGround = new CBackground;
	//pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_3_AfterLayer_0", L"texture\\Map\\Brotherhood\\1-3\\1_3_AfterLayer_0.png"));
	//pBackGround->SetPos(Vec2(-10.f, -20.f));
	//pBackGround->SetScale(Vec2(2.f, 2.f));
	//AddObject(LAYER::FOREGROUND, pBackGround);

	// Foreground 3
	//pBackGround = new CBackground;
	//pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_3_AfterParallax_0", L"texture\\Map\\Brotherhood\\1-3\\1_3_AfterParallax_0.png"));
	//pBackGround->SetParallaxSpeed(Vec2(1.1f, 1.1f));
	//pBackGround->SetPos(Vec2(0.f, 400.f));
	//pBackGround->SetScale(Vec2(2.f, 2.f));
	//AddObject(LAYER::FOREGROUND, pBackGround);


	// Alter
	CTexObj* pObj = new CTexObj;
	pObj->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"Alter", L"texture\\Object\\penitences-altar-off.png"));
	pObj->SetPos(Vec2(2570.f, 1150.f));
	AddObject(LAYER::MAP_OBJECT, pObj);

	// Priedieu
	CPriedieu* pPriedieu = new CPriedieu;
	pPriedieu->SetPos(Vec2(1816.f, 1160.f));
	pPriedieu->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::MAP_OBJECT, pPriedieu);

	// Platform
	CPlatform* pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(1640.f, 1160.f));
	pPlatform->SetScale(Vec2(3200.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	// UI 생성
	CPenitentUI* pPenitentUI = new CPenitentUI;
	AddObject(LAYER::UI, pPenitentUI);

	CTearsUI* pTearsUI = new CTearsUI;
	AddObject(LAYER::UI, pTearsUI);


}

void CStage01_3::enter()
{
	//Penitent 생성
	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();
	
	pPenitent->SetPos(Vec2(150.f, 1178.f));
	pPenitent->SetLeft(false);
	

	if (pPenitent->GetState() == (UINT)PENITENT_STATE::NONE)
	{
		pPenitent->SetState(PENITENT_STATE::RESPAWN);
		pPenitent->SetPos(Vec2(1816.f, 1160.f));
	}
	else if ((UINT)LEVEL_TYPE::STAGE01_2 == CLevelMgr::GetInst()->GetPrevLevel())
	{
		pPenitent->SetState(PENITENT_STATE::IDLE);
		pPenitent->SetPos(Vec2(150.f, 1178.f));
	}
	else if ((UINT)LEVEL_TYPE::STAGE01_4 == CLevelMgr::GetInst()->GetPrevLevel())
	{
		pPenitent->SetState(PENITENT_STATE::IDLE);
		pPenitent->SetPos(Vec2(3180.f, 1178.f));
	}


	AddObject(LAYER::PLAYER, pPenitent);

	// 카메라 설정
	CCamera::GetInst()->FadeIn(1.f);
	CCamera::GetInst()->InitLookAt(pPenitent->GetPos());
	CCamera::GetInst()->SetTarget(pPenitent);
	CCamera::GetInst()->SetLookAtOffsetY(-230.f);
	CCamera::GetInst()->SetCameraLimitLT(Vec2(55.f * 2.f, 310.f * 2.f));
	CCamera::GetInst()->SetCameraLimit(Vec2(1615.f * 2.f, 670.f * 2.f));
}

void CStage01_3::exit()
{
	PullOutObject(LAYER::PLAYER);
}

void CStage01_3::tick()
{
	CLevel::tick();

	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();

	if (pPenitent->GetPos().x < 0.f * 2 && !pPenitent->GetIsLeft())
	{
		CCamera::GetInst()->FixLookAt();
		pPenitent->SetLeft(true);
		pPenitent->SetState(PENITENT_STATE::NONE);

		CCamera::GetInst()->FadeOut(0.5f, LEVEL_TYPE::STAGE01_2);
	}

	if (pPenitent->GetPos().x > 1610.f * 2 && !pPenitent->GetIsLeft())
	{
		CCamera::GetInst()->FixLookAt();
		pPenitent->SetLeft(true);
		pPenitent->SetState(PENITENT_STATE::NONE);

		CCamera::GetInst()->FadeOut(0.5f, LEVEL_TYPE::STAGE01_4);
	}
}
