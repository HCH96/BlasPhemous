#include "pch.h"
#include "CStage02_1.h"

#include "CEngine.h"

#include "CAssetMgr.h"

#include "CBackground.h"

#include "CPenitent.h"

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
	AddObject(LAYER::TILE, pBackGround);
}

void CStage02_1::enter()
{
	//Penitent 생성
	//CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();
	//pPenitent->SetPos(Vec2(1000.f, 1000.f));
	//AddObject(LAYER::PLAYER, pPenitent);

	// 카메라 설정
	Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;

	CCamera::GetInst()->InitLookAt(vLookAt);
	//CCamera::GetInst()->SetTarget(pPenitent);
	//CCamera::GetInst()->SetLookAtOffsetY(-230.f);
	CCamera::GetInst()->SetCameraLimitLT(Vec2(90.f * 2.f, 60.f * 2.f));
	CCamera::GetInst()->SetCameraLimit(Vec2(2050.f * 2.f, 800.f * 2.f));
}

void CStage02_1::exit()
{
}

void CStage02_1::tick()
{
	CLevel::tick();
}
