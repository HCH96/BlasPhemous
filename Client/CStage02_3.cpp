#include "pch.h"
#include "CStage02_3.h"

#include "CEngine.h"

#include "CAssetMgr.h"

#include "CBackground.h"

#include "CPenitent.h"
#include "CPlatform.h"
#include "CPenitentUI.h"
#include "CTearsUI.h"


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


	// Tile 
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"12_3_Tile", L"texture\\Map\\DeambulatoryOfHisHoliness\\12-3\\12_3_Tile.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::TILE, pBackGround);


	CPlatform* pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(1168.f, 1000.f));
	pPlatform->SetScale(Vec2(2200.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);
}

void CStage02_3::enter()
{
	//Penitent 생성
	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();
	pPenitent->SetState(PENITENT_STATE::IDLE);
	pPenitent->SetPos(Vec2(1168.f, 1000.f));
	pPenitent->SetLeft(false);

	AddObject(LAYER::PLAYER, pPenitent);

	// 카메라 설정
	CCamera::GetInst()->FadeIn(1.f);
	CCamera::GetInst()->InitLookAt(pPenitent->GetPos());
	CCamera::GetInst()->SetCameraLimitLT(Vec2(350.f * 2.f, 170.f * 2.f));
	CCamera::GetInst()->SetCameraLimit(Vec2(990.f * 2.f, 530.f * 2.f));
}

void CStage02_3::exit()
{
}

void CStage02_3::tick()
{
	CLevel::tick();
}
