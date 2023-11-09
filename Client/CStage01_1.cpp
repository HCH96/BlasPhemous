#include "pch.h"
#include "CStage01_1.h"

#include "CEngine.h"

#include "CAssetMgr.h"
#include "CTexture.h"

#include "CCamera.h"
#include "CKeyMgr.h"

#include "CPenitent.h"
#include "CPlatform.h"

#include "CImage.h"
#include "CBackground.h"


void CStage01_1::init()
{

	// Background 0
	CBackground* pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_1_BeforeParallax_0", L"texture\\Map\\Brotherhood\\1-1\\1_1_BeforeParallax_0.png"));
	pBackGround->SetParallaxSpeed(Vec2(0.2f,0.3f));
	pBackGround->SetPos(Vec2(0.f, -500.f));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::BACKGROUND, pBackGround);

	// Background 1
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_1_BeforeParallax_1", L"texture\\Map\\Brotherhood\\1-1\\1_1_BeforeParallax_1.png"));
	pBackGround->SetParallaxSpeed(Vec2(0.4f, 0.6f));
	pBackGround->SetPos(Vec2(-850.f, -1000.f));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::BACKGROUND, pBackGround);

	// Background 2
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_1_BeforeParallax_2", L"texture\\Map\\Brotherhood\\1-1\\1_1_BeforeParallax_2.png"));
	pBackGround->SetParallaxSpeed(Vec2(0.5f, 0.75f));
	pBackGround->SetPos(Vec2(-300.f, -300.f));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::BACKGROUND, pBackGround);

	// Tile 
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_1_Tile", L"texture\\Map\\Brotherhood\\1-1\\1_1_Tile.png"));
	pBackGround->SetScale(Vec2(2.f,2.f));
	AddObject(LAYER::TILE, pBackGround);

	// Foreground 1
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_1_Door", L"texture\\Map\\Brotherhood\\1-1\\1_1_Door.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::FOREGROUND, pBackGround);

	// Foreground 2
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_1_AfterLayer", L"texture\\Map\\Brotherhood\\1-1\\1_1_AfterLayer.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::FOREGROUND, pBackGround);


	// 플랫폼 생성
	CPlatform* pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(1000.f, 1200.f));
	AddObject(LAYER::PLATFORM, pPlatform);


}

void CStage01_1::enter()
{

	//Penitent 생성
	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();
	pPenitent->SetPos(Vec2(1000.f, 1000.f));
	AddObject(LAYER::PLAYER, pPenitent);

	// 카메라 설정
	Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;

	CCamera::GetInst()->InitLookAt(vLookAt);
	CCamera::GetInst()->SetCameraLimit(Vec2(1920.f * 2.f, 1027.f * 2.f));
	CCamera::GetInst()->SetTarget(pPenitent);
	CCamera::GetInst()->SetLookAtOffsetY(-230.f);
}

void CStage01_1::exit()
{
	PullOutObject(LAYER::PLAYER);
}

void CStage01_1::tick()
{
	CLevel::tick();

	if (KEY_TAP(KEY::N))
	{
		ChangeLevel(LEVEL_TYPE::TEST_LEVEL);
	}
}
