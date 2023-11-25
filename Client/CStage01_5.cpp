#include "pch.h"
#include "CStage01_5.h"

#include "CEngine.h"

#include "CAssetMgr.h"

#include "CBackground.h"

#include "CPenitent.h"
#include "CPlatform.h"
#include "CPenitentUI.h"
#include "CTearsUI.h"
#include "CCage.h"
#include "CSwitch.h"

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


	CPlatform* pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(1020.f, 772.f));
	pPlatform->SetScale(Vec2(1500.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	CCage* pCage = new CCage;
	pCage->SetPos(Vec2(1450.f, 510.f));
	pCage->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::MAP_OBJECT, pCage);
	
	CSwitch* pSwitch = new CSwitch(pCage);
	pSwitch->SetPos(Vec2(1350.f, 360.f));
	pSwitch->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::MAP_OBJECT, pSwitch);


	// UI 생성
	CPenitentUI* pPenitentUI = new CPenitentUI;
	AddObject(LAYER::UI, pPenitentUI);

	CTearsUI* pTearsUI = new CTearsUI;
	AddObject(LAYER::UI, pTearsUI);

}

void CStage01_5::enter()
{
	//Penitent 생성
	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();
	pPenitent->SetState(PENITENT_STATE::IDLE);
	pPenitent->SetPos(Vec2(460.f, 756.f));
	pPenitent->SetLeft(false);
	if ((UINT)LEVEL_TYPE::STAGE01_4 == CLevelMgr::GetInst()->GetPrevLevel())
	{
		pPenitent->SetPos(Vec2(460.f, 756.f));
	}

	if ((UINT)LEVEL_TYPE::STAGE02_1 == CLevelMgr::GetInst()->GetPrevLevel())
	{
		pPenitent->SetPos(Vec2(1560.f, 756.f));
	}
	AddObject(LAYER::PLAYER, pPenitent);

	// 카메라 설정
	CCamera::GetInst()->FadeIn(1.f);
	CCamera::GetInst()->InitLookAt(pPenitent->GetPos());
	CCamera::GetInst()->SetTarget(pPenitent);
	CCamera::GetInst()->SetLookAtOffsetY(-230.f);
	CCamera::GetInst()->SetCameraLimitLT(Vec2(180.f * 2.f, 80.f * 2.f));
	CCamera::GetInst()->SetCameraLimit(Vec2(792.f * 2.f, 420.f * 2.f));

	// BGM
	CSound* pBGM = CAssetMgr::GetInst()->LoadSound(L"Brotherhood_Ambient", L"sound\\BGM\\Brotherhood_Ambient.wav");
	pBGM->SetVolume(30.f);
	pBGM->PlayToBGM(true);

}

void CStage01_5::exit()
{
	PullOutObject(LAYER::PLAYER);
}

void CStage01_5::tick()
{
	CLevel::tick();

	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();

	if (pPenitent->GetPos().x < 180.f * 2 && !pPenitent->GetIsLeft())
	{
		CCamera::GetInst()->FixLookAt();
		pPenitent->SetLeft(true);
		pPenitent->SetState(PENITENT_STATE::NONE);

		CCamera::GetInst()->FadeOut(0.5f, LEVEL_TYPE::STAGE01_4);
	}

	if (pPenitent->GetPos().x > 790.f * 2 && !pPenitent->GetIsLeft())
	{
		CCamera::GetInst()->FixLookAt();
		pPenitent->SetLeft(true);
		pPenitent->SetState(PENITENT_STATE::NONE);

		CCamera::GetInst()->FadeOut(0.5f, LEVEL_TYPE::STAGE02_1);
	}
}
