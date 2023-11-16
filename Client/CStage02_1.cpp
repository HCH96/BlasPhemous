#include "pch.h"
#include "CStage02_1.h"

#include "CEngine.h"

#include "CAssetMgr.h"

#include "CBackground.h"

#include "CPenitent.h"
#include "CPlatform.h"
#include "CWall.h"
#include "CDeathObj.h"
#include "CPenitentUI.h"
#include "CTearsUI.h"

#include "CCrosscrawler.h"
#include "CLionhead.h"


void CStage02_1::init()
{
	// Background 0
	CBackground* pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"2_1_BeforeParallax_0", L"texture\\Map\\BuriedChurches\\2-1\\2_1_BeforeParallax_0.png"));
	pBackGround->SetParallaxSpeed(Vec2(0.1f, 0.05f));
	AddObject(LAYER::BACKGROUND, pBackGround);

	// Background 1
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"2_1_BeforeParallax_1", L"texture\\Map\\BuriedChurches\\2-1\\2_1_BeforeParallax_1.png"));
	pBackGround->SetParallaxSpeed(Vec2(0.7f, 0.9f));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::BACKGROUND, pBackGround);

	// Background 2
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"2_1_BeforeParallax_2", L"texture\\Map\\BuriedChurches\\2-1\\2_1_BeforeParallax_2.png"));
	pBackGround->SetParallaxSpeed(Vec2(0.8f, 0.93f));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::BACKGROUND, pBackGround);

	// Background 3
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"2_1_BeforeParallax_3", L"texture\\Map\\BuriedChurches\\2-1\\2_1_BeforeParallax_3.png"));
	pBackGround->SetParallaxSpeed(Vec2(0.9f, 0.96f));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::BACKGROUND, pBackGround);

	// Tile 
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"2_1_Tile", L"texture\\Map\\BuriedChurches\\2-1\\2_1_Tile.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::TILE, pBackGround);

	// Foreground 1
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"2_1_Door", L"texture\\Map\\BuriedChurches\\2-1\\2_1_Door.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::FOREGROUND, pBackGround);

	CPlatform* pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(482.f, 782.f));
	pPlatform->SetScale(Vec2(960.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	



	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(896.f, 910.f));
	pPlatform->SetScale(Vec2(130.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(1100.f, 1174.f));
	pPlatform->SetScale(Vec2(160.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(1480.f, 1170.f));
	pPlatform->SetScale(Vec2(270.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(1616.f, 1436.f));
	pPlatform->SetScale(Vec2(272.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(2400.f, 1436.f));
	pPlatform->SetScale(Vec2(800.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(2662.f, 1182.f));
	pPlatform->SetScale(Vec2(270.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(2996.f, 1316.f));
	pPlatform->SetScale(Vec2(144.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(3730.f, 1436.f));
	pPlatform->SetScale(Vec2(300.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(3786.f, 1310.f));
	pPlatform->SetScale(Vec2(130.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(3786.f, 1174.f));
	pPlatform->SetScale(Vec2(130.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(1882.f, 1310.f));
	pPlatform->SetScale(Vec2(268.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(1750.f, 778.f));
	pPlatform->SetScale(Vec2(1060.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	CCrosscrawler* pCorsscrawler = new CCrosscrawler;
	pCorsscrawler->SetPos(Vec2(1750.f, 778.f));
	pCorsscrawler->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::MONSTER, pCorsscrawler);

	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(3326.f, 778.f));
	pPlatform->SetScale(Vec2(1580.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	CLionhead* pLionhead = new CLionhead;
	pLionhead->SetPos(Vec2(3326.f, 778.f));
	pLionhead->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::MONSTER, pLionhead);

	CWall* pWall = new CWall;
	pWall->SetPos(Vec2(1772.f, 1392.f));
	pWall->SetScale(Vec2(60.f, 140.f));
	AddObject(LAYER::PLATFORM, pWall);

	pWall = new CWall;
	pWall->SetPos(Vec2(1966.f, 1392.f));
	pWall->SetScale(Vec2(60.f, 140.f));
	AddObject(LAYER::PLATFORM, pWall);

	pWall = new CWall;
	pWall->SetPos(Vec2(1514.f, 1534.f));
	pWall->SetScale(Vec2(70.f, 190.f));
	AddObject(LAYER::PLATFORM, pWall);

	pWall = new CWall;
	pWall->SetPos(Vec2(3880.f, 1142.f));
	pWall->SetScale(Vec2(60.f, 660.f));
	AddObject(LAYER::PLATFORM, pWall);

	CDeathObj* pDeathObj = new CDeathObj;
	pDeathObj->SetPos(Vec2(3200.f,1500.f));
	pDeathObj->SetScale(Vec2(900.f, 60.f));
	AddObject(LAYER::PLATFORM, pDeathObj);

	pDeathObj = new CDeathObj;
	pDeathObj->SetPos(Vec2(800.f, 1800.f));
	pDeathObj->SetScale(Vec2(1600.f, 100.f));
	AddObject(LAYER::PLATFORM, pDeathObj);

	// UI 생성
	CPenitentUI* pPenitentUI = new CPenitentUI;
	AddObject(LAYER::UI, pPenitentUI);

	CTearsUI* pTearsUI = new CTearsUI;
	AddObject(LAYER::UI, pTearsUI);

}

void CStage02_1::enter()
{
	//Penitent 생성
	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();
	pPenitent->SetState(PENITENT_STATE::IDLE);
	pPenitent->SetPos(Vec2(246.f, 762.f));
	pPenitent->SetLeft(false);
	if ((UINT)LEVEL_TYPE::STAGE01_5 == CLevelMgr::GetInst()->GetPrevLevel())
	{
		pPenitent->SetPos(Vec2(246.f, 762.f));
	}

	if ((UINT)LEVEL_TYPE::STAGE02_1 == CLevelMgr::GetInst()->GetPrevLevel())
	{
		pPenitent->SetPos(Vec2(3860.f, 762.f));
	}
	AddObject(LAYER::PLAYER, pPenitent);

	// 카메라 설정
	CCamera::GetInst()->FadeIn(1.f);
	CCamera::GetInst()->SetLookAtOffsetY(-50.f);
	CCamera::GetInst()->InitLookAt(pPenitent->GetPos());
	CCamera::GetInst()->SetTarget(pPenitent);
	CCamera::GetInst()->SetCameraLimitLT(Vec2(90.f * 2.f, 60.f * 2.f));
	CCamera::GetInst()->SetCameraLimit(Vec2(2050.f * 2.f, 800.f * 2.f));
}

void CStage02_1::exit()
{
	PullOutObject(LAYER::PLAYER);
}

void CStage02_1::tick()
{
	CLevel::tick();

	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();

	if (pPenitent->GetPos().x < 100.f * 2 && !pPenitent->GetIsLeft())
	{
		CCamera::GetInst()->FixLookAt();
		pPenitent->SetLeft(true);
		pPenitent->SetState(PENITENT_STATE::NONE);

		CCamera::GetInst()->FadeOut(0.5f, LEVEL_TYPE::STAGE01_5);
	}

	if (pPenitent->GetPos().x > 2005.f * 2 && !pPenitent->GetIsLeft())
	{
		CCamera::GetInst()->FixLookAt();
		pPenitent->SetLeft(true);
		pPenitent->SetState(PENITENT_STATE::NONE);

		CCamera::GetInst()->FadeOut(0.5f, LEVEL_TYPE::STAGE02_2);
	}
}
