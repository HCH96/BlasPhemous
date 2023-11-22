#include "pch.h"
#include "CStage01_1.h"

#include "CEngine.h"

#include "CAssetMgr.h"
#include "CTexture.h"

#include "CCamera.h"
#include "CKeyMgr.h"

#include "CBackground.h"
#include "CPlatform.h"
#include "CWall.h"

#include "CPenitent.h"
#include "CPenitentUI.h"
#include "CTearsUI.h"


void CStage01_1::init()
{

	//Background 0
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
	pBackGround->SetPos(Vec2(-300.f, -200.f));
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


	// 敲阀汽 积己
	CPlatform* pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(280.f, 1440.f));
	pPlatform->SetScale(Vec2(200.f,30.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(720.f, 1240.f));
	pPlatform->SetScale(Vec2(800.f, 30.f));
	pPlatform->SetAngle(-27.f);
	AddObject(LAYER::PLATFORM, pPlatform);

	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(1220.f, 1060.f));
	pPlatform->SetScale(Vec2(300.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(2120.f, 1440.f));
	pPlatform->SetScale(Vec2(1680.f, 30.f));
	pPlatform->SetAngle(27.f);
	AddObject(LAYER::PLATFORM, pPlatform);

	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(3300.f, 1830.f));
	pPlatform->SetScale(Vec2(1000.f, 30.f));
	AddObject(LAYER::PLATFORM, pPlatform);


	// Wall 积己
	CWall* pWall = new CWall;
	pWall->SetPos(Vec2(130.f, 900.f));
	pWall->SetScale(Vec2(100.f, 1060.f));
	AddObject(LAYER::PLATFORM, pWall);


	// UI 积己
	CPenitentUI* pPenitentUI = new CPenitentUI;
	AddObject(LAYER::UI, pPenitentUI);

	CTearsUI* pTearsUI = new CTearsUI;
	AddObject(LAYER::UI, pTearsUI);


	// Sound Load
	CAssetMgr::GetInst()->LoadSound(L"Brotherhood_Ambient", L"sound\\BGM\\Brotherhood_Ambient.wav");

}

void CStage01_1::enter()
{
	//Penitent 积己
	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();
	if ((UINT)LEVEL_TYPE::STAGE01_2 == CLevelMgr::GetInst()->GetPrevLevel())
	{
		pPenitent->SetPos(Vec2(1845.f*2, 895.f*2));
		pPenitent->SetState(PENITENT_STATE::IDLE);
	}
	else
	{
		pPenitent->SetPos(Vec2(1200.f, 0.f));
		pPenitent->SetState(PENITENT_STATE::FALLINGAHEAD);
	}
	pPenitent->SetLeft(false);
	AddObject(LAYER::PLAYER, pPenitent);

	// 墨皋扼 汲沥
	CCamera::GetInst()->FadeIn(1.f);

	Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;

	CCamera::GetInst()->SetTarget(pPenitent);
	CCamera::GetInst()->InitLookAt(pPenitent->GetPos());
	CCamera::GetInst()->SetLookAtOffsetY(-230.f);
	CCamera::GetInst()->SetCameraLimitLT(Vec2(0.f * 2.f, 0.f * 2.f));
	CCamera::GetInst()->SetCameraLimit(Vec2(1920.f * 2.f, 1027.f * 2.f));

	// Sound 
	CSound* pBGM = CAssetMgr::GetInst()->LoadSound(L"Brotherhood_Ambient", L"sound\\BGM\\Brotherhood_Ambient.wav");
	pBGM->PlayToBGM(true);

}

void CStage01_1::exit()
{
	PullOutObject(LAYER::PLAYER);
}

void CStage01_1::tick()
{
	CLevel::tick();

	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();

	if (pPenitent->GetPos().x > 1845.f * 2 && !pPenitent->GetIsLeft())
	{
		CCamera::GetInst()->FixLookAt();
		pPenitent->SetLeft(true);
		pPenitent->SetState(PENITENT_STATE::NONE);

		CCamera::GetInst()->FadeOut(0.5f, LEVEL_TYPE::STAGE01_2);
	}
}
