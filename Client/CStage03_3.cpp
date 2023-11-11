#include "pch.h"
#include "CStage03_3.h"

#include "CEngine.h"

#include "CAssetMgr.h"

#include "CBackground.h"

#include "CPenitent.h"

void CStage03_3::init()
{
	// Tile 
	CBackground* pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"Shop_Tile", L"texture\\Map\\Shop\\15-1\\Shop_Tile.png"));
	AddObject(LAYER::TILE, pBackGround);

	// Foreground 1
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"Shop_AfterLayer", L"texture\\Map\\Shop\\15-1\\Shop_AfterLayer.png"));
	pBackGround->SetPos(Vec2(0.f, -70.f));
	AddObject(LAYER::FOREGROUND, pBackGround);
}

void CStage03_3::enter()
{
	//Penitent 생성
	//CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();
	//pPenitent->SetPos(Vec2(1000.f, 1000.f));
	//AddObject(LAYER::PLAYER, pPenitent);

	// 카메라 설정 (고정)

	CCamera::GetInst()->InitLookAt(Vec2(950.f, 450.f));
	CCamera::GetInst()->SetLookAt(Vec2(950.f,450.f));
}

void CStage03_3::exit()
{
}

void CStage03_3::tick()
{
	CLevel::tick();
}
