#include "pch.h"
#include "CStage02_3.h"

#include "CEngine.h"

#include "CAssetMgr.h"

#include "CBackground.h"

#include "CPenitent.h"
#include "CPlatform.h"
#include "CPenitentUI.h"
#include "CTearsUI.h"

#include "CWall.h"
#include "CTwisterBackground.h"
#include "CAshPlatform.h"

#include "CGiantSword.h"
#include "Pontiff.h"


void CStage02_3::init()
{
	//Background 0
	CBackground* pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"12_3_BeforeLayer_0", L"texture\\Map\\DeambulatoryOfHisHoliness\\12-3\\12_3_BeforeLayer_0.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::BACKGROUND, pBackGround);

	//Background 1
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"12_3_BeforeLayer_1", L"texture\\Map\\DeambulatoryOfHisHoliness\\12-3\\12_3_BeforeLayer_1.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::BACKGROUND, pBackGround);

	// TwisterBackground

	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"Twister", L"texture\\Effect\\pontif-twister-background.png");
	CTwisterBackground* pTwister = new CTwisterBackground;
	pTwister->SetPos(Vec2(0.f, 0.f));
	pTwister->SetTexture(pTex);
	pTwister->SetAlpha(50.f);
	pTwister->SetMaxAlpha(100.f);
	pTwister->SetMinAlpha(30.f);
	AddObject(LAYER::BACKGROUND, pTwister);

	pTex = CAssetMgr::GetInst()->LoadTexture(L"Twister_Fore", L"texture\\Effect\\pontif-twister-foreground.png");
	pTwister = new CTwisterBackground;
	pTwister->SetPos(Vec2(480.f, 0.f));
	pTwister->SetTexture(pTex);
	pTwister->SetAlpha(255.f);
	pTwister->SetMaxAlpha(255.f);
	pTwister->SetMinAlpha(255.f);
	AddObject(LAYER::FOREGROUND, pTwister);


	// Tile 
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"12_3_Tile", L"texture\\Map\\DeambulatoryOfHisHoliness\\12-3\\12_3_Tile.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::TILE, pBackGround);


	// Platform
	CPlatform* pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(1340.f, 1000.f));
	pPlatform->SetScale(Vec2(2200.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	CWall* pWall = new CWall;
	pWall->SetPos(Vec2(670.f, 700.f));
	pWall->SetScale(Vec2(30.f, 1000.f));
	AddObject(LAYER::PLATFORM, pWall);

	pWall = new CWall;
	pWall->SetPos(Vec2(2010.f, 700.f));
	pWall->SetScale(Vec2(30.f, 1000.f));
	AddObject(LAYER::PLATFORM, pWall);

	// 1번 그룹
	CAshPlatform* pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(780.f, 700.f));
	pAshPlatform->SetAcc(12.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);

	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(1900.f, 700.f));
	pAshPlatform->SetAcc(12.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);

	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(920.f, 850.f));
	pAshPlatform->SetAcc(12.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);

	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(1760.f, 850.f));
	pAshPlatform->SetAcc(12.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);

	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(1060.f, 700.f));
	pAshPlatform->SetAcc(12.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);

	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(1620.f, 700.f));
	pAshPlatform->SetAcc(12.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);

	// 2번 그룹
	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(780.f, 850.f));
	pAshPlatform->SetAcc(8.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);

	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(1900.f, 850.f));
	pAshPlatform->SetAcc(8.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);

	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(1200.f, 700.f));
	pAshPlatform->SetAcc(8.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);

	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(1480.f, 700.f));
	pAshPlatform->SetAcc(8.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);

	// 3번 그룹
	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(920.f, 700.f));
	pAshPlatform->SetAcc(4.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);

	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(1760.f, 700.f));
	pAshPlatform->SetAcc(4.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);

	// 4번 그룹
	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(1060.f, 850.f));
	pAshPlatform->SetAcc(0.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);

	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(1620.f, 850.f));
	pAshPlatform->SetAcc(0.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);


	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(1200.f, 775.f));
	pAshPlatform->SetAcc(0.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);

	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(1480.f, 775.f));
	pAshPlatform->SetAcc(0.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);


	// Boss
	Pontiff* pPontiff = new Pontiff;
	pPontiff->SetPos(Vec2(1340.f, 1000.f));
	AddObject(LAYER::STATIC_MONSTER, pPontiff);


	CGiantSword* pSword = new CGiantSword;
	pSword->SetPos(Vec2(1480.f, 275.f));
	AddObject(LAYER::MONSTER, pSword);

	pPontiff->RegisterSword(pSword);


	// UI 
	CPenitentUI* pPenitentUI = new CPenitentUI;
	AddObject(LAYER::UI, pPenitentUI);

	CTearsUI* pTearsUI = new CTearsUI;
	AddObject(LAYER::UI, pTearsUI);

}

void CStage02_3::enter()
{
	//Penitent 생성
	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();
	pPenitent->SetState(PENITENT_STATE::IDLE);
	pPenitent->SetPos(Vec2(1370.f, 1000.f));
	pPenitent->SetLeft(false);

	AddObject(LAYER::PLAYER, pPenitent);

	// 카메라 설정
	CCamera::GetInst()->FadeIn(1.f);
	CCamera::GetInst()->InitLookAt(pPenitent->GetPos());
	CCamera::GetInst()->SetCameraLimitLT(Vec2(350.f * 2.f, 150.f * 2.f));
	CCamera::GetInst()->SetCameraLimit(Vec2(990.f * 2.f, 510.f * 2.f));
}

void CStage02_3::exit()
{
}

void CStage02_3::tick()
{
	CLevel::tick();
}
