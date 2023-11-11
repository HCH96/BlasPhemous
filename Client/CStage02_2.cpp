#include "pch.h"
#include "CStage02_2.h"

#include "CEngine.h"

#include "CAssetMgr.h"

#include "CBackground.h"

#include "CPenitent.h"

void CStage02_2::init()
{
	//Background 0
	CBackground* pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"12_2_BeforeParallax_0", L"texture\\Map\\DeambulatoryOfHisHoliness\\12-2\\12_2_BeforeParallax_0.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	pBackGround->SetPos(Vec2(0.f, 200.f));
	pBackGround->SetParallaxSpeed(Vec2(0.5f, 1.f));
	AddObject(LAYER::BACKGROUND, pBackGround);


	// Tile 
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"12_2_Tile", L"texture\\Map\\DeambulatoryOfHisHoliness\\12-2\\12_2_Tile.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::TILE, pBackGround);

	// Foreground 1
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"12_2_AfterLayer", L"texture\\Map\\DeambulatoryOfHisHoliness\\12-2\\12_2_AfterLayer.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::TILE, pBackGround);

}

void CStage02_2::enter()
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
	CCamera::GetInst()->SetCameraLimitLT(Vec2(90.f * 2.f, 570.f * 2.f));
	CCamera::GetInst()->SetCameraLimit(Vec2(2030.f * 2.f, 930.f * 2.f));
}

void CStage02_2::exit()
{
}

void CStage02_2::tick()
{
	CLevel::tick();
}
