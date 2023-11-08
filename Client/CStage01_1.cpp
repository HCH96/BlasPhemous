#include "pch.h"
#include "CStage01_1.h"

#include "CEngine.h"

#include "CAssetMgr.h"
#include "CTexture.h"

#include "CCamera.h"
#include "CKeyMgr.h"

#include "CPenitent.h"


#include "CImage.h"


void CStage01_1::init()
{

	//CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"1_1_Tile", L"texture\\Map\\Brotherhood\\1-1\\tile.png");

	CImage* pImage = new CImage;
	pImage->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_1_Tile", L"texture\\Map\\Brotherhood\\1-1\\tile.png"));
	pImage->SetScale(pImage->GetScale() * 2);
	//pImage->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"1_1_Tile", L"texture\\Penitent\\threeAnguishBigBeamBlue.png"));
	pImage->SetScaleToTex();
	pImage->SetPos(Vec2(960.f, 515.f));
	AddObject(LAYER::DEFAULT, pImage);

}

void CStage01_1::enter()
{
	// 카메라 설정
	Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;

	// Penitent 생성
	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();
	pPenitent->SetPos(vLookAt);
	AddObject(LAYER::PLAYER, pPenitent);

	CCamera::GetInst()->InitLookAt(vLookAt);

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
		ChangeLevel(LEVEL_TYPE::PLAY_LEVEL);
	}
}
