#include "pch.h"
#include "CStage01_5.h"

#include "CEngine.h"

#include "CAssetMgr.h"

#include "CBackground.h"

#include "CPenitent.h"

void CStage01_5::init()
{


	// Tile 
	CBackground* pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_5_Tile", L"texture\\Map\\Brotherhood\\1-5\\1_5_Tile.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::TILE, pBackGround);

	// Foreground 1
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_5_Door", L"texture\\Map\\Brotherhood\\1-5\\1_5_Door.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::FOREGROUND, pBackGround);

	// Foreground 2
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_5_AfterLayer", L"texture\\Map\\Brotherhood\\1-5\\1_5_AfterLayer.png"));
	pBackGround->SetPos(Vec2(100.f, 0.f));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::FOREGROUND, pBackGround);
}

void CStage01_5::enter()
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
	CCamera::GetInst()->SetCameraLimitLT(Vec2(150.f * 2.f, 80.f * 2.f));
	CCamera::GetInst()->SetCameraLimit(Vec2(1430.f * 2.f, 440.f * 2.f));
}

void CStage01_5::exit()
{
}

void CStage01_5::tick()
{
	CLevel::tick();
}
