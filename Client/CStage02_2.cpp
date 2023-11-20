#include "pch.h"
#include "CStage02_2.h"

#include "CEngine.h"

#include "CAssetMgr.h"

#include "CBackground.h"

#include "CPenitent.h"
#include "CPlatform.h"
#include "CPenitentUI.h"
#include "CTearsUI.h"

#include "CBossPanel.h"

#include "CPope.h"

#include "CFirebolt.h"
#include "CFireboltSpawner.h"

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


	CPlatform* pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(2250.f, 1740.f));
	pPlatform->SetScale(Vec2(4430.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);


	// Boss
	CPope* pPope = new CPope;
	pPope->SetPos(Vec2(2250.f, 1740.f));
	pPope->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::MONSTER, pPope);


	// Firebolt
	CFireboltSpawner* pFireSpawner = new CFireboltSpawner;
	AddObject(LAYER::SPAWNER, pFireSpawner);
	pPope->RegisterFireSpawner(pFireSpawner);


	CFirebolt* pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);



	// UI 생성
	CPenitentUI* pPenitentUI = new CPenitentUI;
	AddObject(LAYER::UI, pPenitentUI);

	CTearsUI* pTearsUI = new CTearsUI;
	AddObject(LAYER::UI, pTearsUI);

	RegisterBoss(pPope);

	CBossPanel* pBossPanel = new CBossPanel;
	AddObject(LAYER::UI, pBossPanel);

}

void CStage02_2::enter()
{
	//Penitent 생성
	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();
	pPenitent->SetState(PENITENT_STATE::IDLE);
	pPenitent->SetPos(Vec2(240.f, 1740.f));
	pPenitent->SetLeft(false);
	if ((UINT)LEVEL_TYPE::STAGE02_1 == CLevelMgr::GetInst()->GetPrevLevel())
	{
		pPenitent->SetPos(Vec2(240.f, 1740.f));
	}

	if ((UINT)LEVEL_TYPE::STAGE02_3 == CLevelMgr::GetInst()->GetPrevLevel())
	{
		pPenitent->SetPos(Vec2(2264.f, 1740.f));
	}
	AddObject(LAYER::PLAYER, pPenitent);

	// 카메라 설정
	CCamera::GetInst()->FadeIn(1.f);
	CCamera::GetInst()->SetLookAtOffsetY(-50.f);
	CCamera::GetInst()->InitLookAt(pPenitent->GetPos());
	CCamera::GetInst()->SetTarget(pPenitent);
	CCamera::GetInst()->SetCameraLimitLT(Vec2(90.f * 2.f, 580.f * 2.f));
	CCamera::GetInst()->SetCameraLimit(Vec2(2030.f * 2.f, 940.f * 2.f));
}

void CStage02_2::exit()
{
}

void CStage02_2::tick()
{
	CLevel::tick();



}
