#include "pch.h"
#include "CStage01_2.h"

#include "CEngine.h"

#include "CAssetMgr.h"

#include "CBackground.h"

#include "CPenitent.h"



void CStage01_2::init()
{
	// Background 0
	CBackground* pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_2_BeforeParallax_0", L"texture\\Map\\Brotherhood\\1-2\\1_2_BeforeParallax_0.png"));
	pBackGround->SetParallaxSpeed(Vec2(0.2f, 0.3f));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::BACKGROUND, pBackGround);

	//// Background 1
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_2_BeforeParallax_1", L"texture\\Map\\Brotherhood\\1-2\\1_2_BeforeParallax_1.png"));
	pBackGround->SetParallaxSpeed(Vec2(0.3f, 0.6f));
	pBackGround->SetPos(Vec2(0.f, 130.f));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::BACKGROUND, pBackGround);

	//// Background 2
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_2_BeforeParallax_2", L"texture\\Map\\Brotherhood\\1-2\\1_2_BeforeParallax_2.png"));
	pBackGround->SetParallaxSpeed(Vec2(0.4f, 0.75f));
	pBackGround->SetPos(Vec2(-650.f, -240.f));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::BACKGROUND, pBackGround);

	// Background 3
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_2_BeforeParallax_3", L"texture\\Map\\Brotherhood\\1-2\\1_2_BeforeParallax_3.png"));
	pBackGround->SetParallaxSpeed(Vec2(0.5f, 0.75f));
	pBackGround->SetPos(Vec2(-200.f, -50.f));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::BACKGROUND, pBackGround);

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
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_2_AfterParallax_0", L"texture\\Map\\Brotherhood\\1-2\\1_2_AfterParallax_01.png"));
	pBackGround->SetParallaxSpeed(Vec2(1.1f, 1.1f));
	pBackGround->SetPos(Vec2(100.f, 80.f));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::FOREGROUND, pBackGround);




}

void CStage01_2::enter()
{
	//Penitent 생성
	//CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();
	//pPenitent->SetPos(Vec2(1000.f, 1000.f));
	//AddObject(LAYER::PLAYER, pPenitent);

	// 카메라 설정
	Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;

	CCamera::GetInst()->InitLookAt(Vec2(762.f,1354.f));
	//CCamera::GetInst()->SetTarget(pPenitent);
	//CCamera::GetInst()->SetLookAtOffsetY(-230.f);
	CCamera::GetInst()->SetCameraLimit(Vec2(2112.f * 2.f, 1130.f * 2.f));

}

void CStage01_2::exit()
{
}

void CStage01_2::tick()
{
	CLevel::tick();
}
