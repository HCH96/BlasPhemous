#include "pch.h"
#include "CStage01_3.h"

#include "CEngine.h"

#include "CAssetMgr.h"

#include "CBackground.h"

#include "CPenitent.h"

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
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_3_BeforeParallax_2", L"texture\\Map\\Brotherhood\\1-3\\1_3_BeforeParallax_2.png"));
	pBackGround->SetParallaxSpeed(Vec2(0.3f, 0.3f));
	pBackGround->SetPos(Vec2(-700.f, -330.f));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::BACKGROUND, pBackGround);

	// Background 3
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_3_BeforeParallax_3", L"texture\\Map\\Brotherhood\\1-3\\1_3_BeforeParallax_3.png"));
	pBackGround->SetParallaxSpeed(Vec2(0.4f, 0.3f));
	pBackGround->SetPos(Vec2(-500.f, -350.f));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::BACKGROUND, pBackGround);

	// Background 4
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_3_BeforeParallax_4", L"texture\\Map\\Brotherhood\\1-3\\1_3_BeforeParallax_4.png"));
	pBackGround->SetParallaxSpeed(Vec2(0.5f, 0.3f));
	pBackGround->SetPos(Vec2(-500.f, -350.f));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::BACKGROUND, pBackGround);


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
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_3_AfterLayer_0", L"texture\\Map\\Brotherhood\\1-3\\1_3_AfterLayer_0.png"));
	pBackGround->SetPos(Vec2(-10.f, -20.f));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::FOREGROUND, pBackGround);

	// Foreground 3
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_3_AfterParallax_0", L"texture\\Map\\Brotherhood\\1-3\\1_3_AfterParallax_0.png"));
	pBackGround->SetParallaxSpeed(Vec2(1.1f, 1.1f));
	pBackGround->SetPos(Vec2(0.f, 400.f));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::FOREGROUND, pBackGround);

}

void CStage01_3::enter()
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
	CCamera::GetInst()->SetCameraLimitLT(Vec2(55.f * 2.f, 310.f * 2.f));
	CCamera::GetInst()->SetCameraLimit(Vec2(1615.f * 2.f, 670.f * 2.f));
}

void CStage01_3::exit()
{
}

void CStage01_3::tick()
{
	CLevel::tick();
}
