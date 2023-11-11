#include "pch.h"
#include "CStage01_4.h"

#include "CEngine.h"

#include "CAssetMgr.h"

#include "CBackground.h"

#include "CPenitent.h"


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
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_4_BeforeParallax_2", L"texture\\Map\\Brotherhood\\1-4\\1_4_BeforeParallax_2.png"));
	pBackGround->SetParallaxSpeed(Vec2(0.5f, 0.3f));
	pBackGround->SetPos(Vec2(0.f, -450.f));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::BACKGROUND, pBackGround);

	// Background 3
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_4_BeforeParallax_3", L"texture\\Map\\Brotherhood\\1-4\\1_4_BeforeParallax_3.png"));
	pBackGround->SetParallaxSpeed(Vec2(0.7f, 0.3f));
	pBackGround->SetPos(Vec2(0.f, 80.f));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::BACKGROUND, pBackGround);

	// Background 3
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
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_4_AfterLayer_0", L"texture\\Map\\Brotherhood\\1-4\\1_4_AfterLayer_0.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::FOREGROUND, pBackGround);

}

void CStage01_4::enter()
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
	CCamera::GetInst()->SetCameraLimitLT(Vec2(100.f * 2.f, 255.f * 2.f));
	CCamera::GetInst()->SetCameraLimit(Vec2(1380.f * 2.f, 615.f * 2.f));
}

void CStage01_4::exit()
{
}

void CStage01_4::tick()
{
	CLevel::tick();
}
