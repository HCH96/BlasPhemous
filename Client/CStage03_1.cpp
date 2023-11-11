#include "pch.h"
#include "CStage03_1.h"

#include "CEngine.h"

#include "CAssetMgr.h"

#include "CBackground.h"

#include "CPenitent.h"

void CStage03_1::init()
{	
	// Tile 
	CBackground* pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"2_2_Tile", L"texture\\Map\\BuriedChurches\\2-2\\2_2_Tile.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::TILE, pBackGround);

	// Foreground 1
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"2_2_Door", L"texture\\Map\\BuriedChurches\\2-2\\2_2_Door.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::FOREGROUND, pBackGround);

}

void CStage03_1::enter()
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
	CCamera::GetInst()->SetCameraLimitLT(Vec2(360.f * 2.f, 230.f * 2.f));
	CCamera::GetInst()->SetCameraLimit(Vec2(1040 * 2.f, 600.f * 2.f));
}

void CStage03_1::exit()
{
}

void CStage03_1::tick()
{
	CLevel::tick();
}
