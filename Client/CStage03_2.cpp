#include "pch.h"
#include "CStage03_2.h"

#include "CEngine.h"

#include "CAssetMgr.h"

#include "CBackground.h"

#include "CPenitent.h"

void CStage03_2::init()
{
	// Tile 
	CBackground* pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"2_3_Tile", L"texture\\Map\\\BuriedChurches\\2-3\\2_3_Tile.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::TILE, pBackGround);

	// Foreground 1
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"2_3_Door", L"texture\\Map\\\BuriedChurches\\2-3\\2_3_Door.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::FOREGROUND, pBackGround);
}

void CStage03_2::enter()
{
	//Penitent ����
	//CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();
	//pPenitent->SetPos(Vec2(1000.f, 1000.f));
	//AddObject(LAYER::PLAYER, pPenitent);

	// ī�޶� ����
	Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;

	CCamera::GetInst()->InitLookAt(vLookAt);
	//CCamera::GetInst()->SetTarget(pPenitent);
	//CCamera::GetInst()->SetLookAtOffsetY(-230.f);
	CCamera::GetInst()->SetCameraLimitLT(Vec2(250.f * 2.f, 190.f * 2.f));
	CCamera::GetInst()->SetCameraLimit(Vec2(1030 * 2.f, 550.f * 2.f));
}

void CStage03_2::exit()
{
}

void CStage03_2::tick()
{
	CLevel::tick();
}
