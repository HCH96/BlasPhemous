#include "pch.h"
#include "CStage01_2.h"

#include "CEngine.h"

#include "CAssetMgr.h"

#include "CBackground.h"

#include "CPenitent.h"

#include "CPlatform.h"
#include "CWall.h"
#include "CLedge.h"
#include "CCandle.h"

#include "CPenitentUI.h"
#include "CTearsUI.h"
#include "CLadder.h"

#include "CFoolKnife.h"


void CStage01_2::init()
{
	// Background 0
	CBackground* pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_2_BeforeParallax_0", L"texture\\Map\\Brotherhood\\1-2\\1_2_BeforeParallax_0.png"));
	pBackGround->SetParallaxSpeed(Vec2(0.2f, 0.3f));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::BACKGROUND, pBackGround);

	// Background 1
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_2_BeforeParallax_1", L"texture\\Map\\Brotherhood\\1-2\\1_2_BeforeParallax_1.png"));
	pBackGround->SetParallaxSpeed(Vec2(0.3f, 0.6f));
	pBackGround->SetPos(Vec2(0.f, 130.f));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::BACKGROUND, pBackGround);

	// Background 2
	//pBackGround = new CBackground;
	//pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_2_BeforeParallax_2", L"texture\\Map\\Brotherhood\\1-2\\1_2_BeforeParallax_2.png"));
	//pBackGround->SetParallaxSpeed(Vec2(0.4f, 0.75f));
	//pBackGround->SetPos(Vec2(-650.f, -240.f));
	//pBackGround->SetScale(Vec2(2.f, 2.f));
	//AddObject(LAYER::BACKGROUND, pBackGround);

	// Background 3
	//pBackGround = new CBackground;
	//pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_2_BeforeParallax_3", L"texture\\Map\\Brotherhood\\1-2\\1_2_BeforeParallax_3.png"));
	//pBackGround->SetParallaxSpeed(Vec2(0.5f, 0.75f));
	//pBackGround->SetPos(Vec2(-200.f, -50.f));
	//pBackGround->SetScale(Vec2(2.f, 2.f));
	//AddObject(LAYER::BACKGROUND, pBackGround);

	//// Background 4
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_2_BeforeParallax_4", L"texture\\Map\\Brotherhood\\1-2\\1_2_BeforeParallax_4.png"));
	pBackGround->SetParallaxSpeed(Vec2(0.6f, 0.75f));
	pBackGround->SetPos(Vec2(-500.f, -730.f));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::BACKGROUND, pBackGround);

	// Tile 
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_2_Tile", L"texture\\Map\\Brotherhood\\1-2\\1_2_Tile.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::TILE, pBackGround);

	// Foreground 1
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_2_Door", L"texture\\Map\\Brotherhood\\1-2\\1_2_Door.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::FOREGROUND, pBackGround);

	// Foreground 2
	//pBackGround = new CBackground;
	//pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_2_AfterParallax_0", L"texture\\Map\\Brotherhood\\1-2\\1_2_AfterParallax_01.png"));
	//pBackGround->SetParallaxSpeed(Vec2(1.1f, 1.1f));
	//pBackGround->SetPos(Vec2(100.f, 80.f));
	//pBackGround->SetScale(Vec2(2.f, 2.f));
	//AddObject(LAYER::FOREGROUND, pBackGround);


	// 플랫폼 생성
	CPlatform* pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(450.f, 1520.f));
	pPlatform->SetScale(Vec2(1000.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(1050.f, 1380.f));
	pPlatform->SetScale(Vec2(260.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	CWall* pWall = new CWall;
	pWall->SetPos(Vec2(940.f, 1480.f));
	pWall->SetScale(Vec2(40.f, 190.f));
	AddObject(LAYER::PLATFORM, pWall);
	
	pWall = new CWall;
	pWall->SetPos(Vec2(1206.f, 1336.f));
	pWall->SetScale(Vec2(60.f, 160.f));
	AddObject(LAYER::PLATFORM, pWall);

	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(1400.f, 1254.f));
	pPlatform->SetScale(Vec2(440.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	CLadder* pLadder = new CLadder;
	pLadder->SetPos(Vec2(1536.f, 1394.f));
	pLadder->SetScale(Vec2(40.f, 280.f));
	AddObject(LAYER::LADDER, pLadder);


	pLadder = new CLadder;
	pLadder->SetPos(Vec2(2400.f, 1400.f));
	pLadder->SetScale(Vec2(40.f, 280.f));
	AddObject(LAYER::LADDER, pLadder);


	CLedge* pLedge = new CLedge;
	pLedge->SetPos(Vec2(1610.f, 1255.f));
	pLedge->SetScale(Vec2(24.f, 50.f));
	AddObject(LAYER::PLATFORM, pLedge);

	pWall = new CWall;
	pWall->SetPos(Vec2(1414.f, 1476.f));
	pWall->SetScale(Vec2(94.f, 418.f));
	AddObject(LAYER::PLATFORM, pWall);

	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(1916.f, 1660.f));
	pPlatform->SetScale(Vec2(1200.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	CFoolKnife* pFoolKnife = new CFoolKnife;
	pFoolKnife->SetPos(Vec2(2100.f, 1660.f));
	pFoolKnife->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::MONSTER, pFoolKnife);

	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(1870.f, 1250.f));
	pPlatform->SetScale(Vec2(200.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	pLedge = new CLedge;
	pLedge->SetPos(Vec2(1780.f, 1251.f));
	pLedge->SetScale(Vec2(24.f, 50.f));
	AddObject(LAYER::PLATFORM, pLedge);

	pLedge = new CLedge;
	pLedge->SetPos(Vec2(1970.f, 1251.f));
	pLedge->SetScale(Vec2(24.f, 50.f));
	AddObject(LAYER::PLATFORM, pLedge);

	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(2800.f, 1260.f));
	pPlatform->SetScale(Vec2(1000.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	pLedge = new CLedge;
	pLedge->SetPos(Vec2(2300.f, 1261.f));
	pLedge->SetScale(Vec2(24.f, 50.f));
	AddObject(LAYER::PLATFORM, pLedge);

	pWall = new CWall;
	pWall->SetPos(Vec2(2640.f, 1500.f));
	pWall->SetScale(Vec2(270.f, 410.f));
	AddObject(LAYER::PLATFORM, pWall);

	pWall = new CWall;
	pWall->SetPos(Vec2(3370.f, 1280.f));
	pWall->SetScale(Vec2(180.f, 600.f));
	AddObject(LAYER::PLATFORM, pWall);

	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(2900.f, 1520.f));
	pPlatform->SetScale(Vec2(260.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	pFoolKnife = new CFoolKnife;
	pFoolKnife->SetPos(Vec2(2900.f, 1520.f));
	pFoolKnife->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::MONSTER, pFoolKnife);

	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(3240.f, 1400.f));
	pPlatform->SetScale(Vec2(140.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	pWall = new CWall;
	pWall->SetPos(Vec2(3000.f, 1600.f));
	pWall->SetScale(Vec2(72.f, 144.f));
	AddObject(LAYER::PLATFORM, pWall);

	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(3580.f, 1670.f));
	pPlatform->SetScale(Vec2(1100.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);


	// Map Object
	CCandle* pCandle = new CCandle(2);
	pCandle->SetPos(Vec2(868.f, 1488.f));
	AddObject(LAYER::MAP_OBJECT, pCandle);

	pCandle = new CCandle(4);
	pCandle->SetPos(Vec2(828.f, 1498.f));
	AddObject(LAYER::MAP_OBJECT, pCandle);

	pCandle = new CCandle(2);
	pCandle->SetPos(Vec2(1114.f, 1366.f));
	AddObject(LAYER::MAP_OBJECT, pCandle);

	pCandle = new CCandle(4);
	pCandle->SetPos(Vec2(1074.f, 1376.f));
	AddObject(LAYER::MAP_OBJECT, pCandle);

	pCandle = new CCandle(2);
	pCandle->SetPos(Vec2(2000.f, 1625.f));
	AddObject(LAYER::MAP_OBJECT, pCandle);

	pCandle = new CCandle(4);
	pCandle->SetPos(Vec2(2025.f, 1635.f));
	AddObject(LAYER::MAP_OBJECT, pCandle);

	pCandle = new CCandle(2);
	pCandle->SetPos(Vec2(2050.f, 1625.f));
	AddObject(LAYER::MAP_OBJECT, pCandle);

	pCandle = new CCandle(4);
	pCandle->SetPos(Vec2(2800.f, 1500.f));
	AddObject(LAYER::MAP_OBJECT, pCandle);

	pCandle = new CCandle(4);
	pCandle->SetPos(Vec2(2820.f, 1500.f));
	AddObject(LAYER::MAP_OBJECT, pCandle);




	// UI 생성
	CPenitentUI* pPenitentUI = new CPenitentUI;
	AddObject(LAYER::UI, pPenitentUI);

	CTearsUI* pTearsUI = new CTearsUI;
	AddObject(LAYER::UI, pTearsUI);


}

void CStage01_2::enter()
{
	//Penitent 생성
	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();
	pPenitent->SetState(PENITENT_STATE::IDLE);
	pPenitent->SetPos(Vec2(170.f, 1500.f));
	pPenitent->SetLeft(false);
	CMovement* pMovement = pPenitent->GetComponent<CMovement>();
	pMovement->SetGround(true);
	if ((UINT)LEVEL_TYPE::STAGE01_1 == CLevelMgr::GetInst()->GetPrevLevel())
	{
		pPenitent->SetPos(Vec2(170.f, 1500.f));
	}

	if ((UINT)LEVEL_TYPE::STAGE01_3 == CLevelMgr::GetInst()->GetPrevLevel())
	{
		pPenitent->SetPos(Vec2(4060.f, 1630.f));
	}
	AddObject(LAYER::PLAYER, pPenitent);


	// 카메라 설정
	CCamera::GetInst()->FadeIn(1.f);
	CCamera::GetInst()->InitLookAt(pPenitent->GetPos());
	CCamera::GetInst()->SetTarget(pPenitent);
	CCamera::GetInst()->SetLookAtOffsetY(-230.f);
	CCamera::GetInst()->SetCameraLimitLT(Vec2(64.f * 2.f, 506.f * 2.f));
	CCamera::GetInst()->SetCameraLimit(Vec2(2043.f * 2.f, 855 * 2.f));
}

void CStage01_2::exit()
{
	PullOutObject(LAYER::PLAYER);
}

void CStage01_2::tick()
{
	CLevel::tick();

	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();

	if (pPenitent->GetPos().x < 0.f * 2 && !pPenitent->GetIsLeft())
	{
		CCamera::GetInst()->FixLookAt();
		pPenitent->SetLeft(true);
		pPenitent->SetState(PENITENT_STATE::NONE);

		CCamera::GetInst()->FadeOut(0.5f, LEVEL_TYPE::STAGE01_1);
	}

	if (pPenitent->GetPos().x > 2034.f * 2 && !pPenitent->GetIsLeft())
	{
		CCamera::GetInst()->FixLookAt();
		pPenitent->SetLeft(true);
		pPenitent->SetState(PENITENT_STATE::NONE);

		CCamera::GetInst()->FadeOut(0.5f, LEVEL_TYPE::STAGE01_3);
	}

}
