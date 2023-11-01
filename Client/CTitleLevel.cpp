#include "pch.h"
#include "CTitleLevel.h"


#include "CEngine.h"

#include "CAssetMgr.h"
#include "CCamera.h"
#include "CKeyMgr.h"

#include "CImage.h"

void CTitleLevel::init()
{
	// 카메라 설정
	Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;

	CCamera::GetInst()->SetLookAt(vLookAt);

	CImage* pImage = new CImage;
	pImage->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"GameLogo", L"texture\\UI\\GameLogo.png"));
	pImage->SetScaleToTex();
	pImage->SetPos(Vec2(640.f, 360.f));
	AddObject(LAYER::DEFAULT, pImage);

	pImage = new CImage;
	pImage->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"PressAnybutton", L"texture\\UI\\PressAnybutton.png"));
	pImage->SetScaleToTex();
	pImage->SetPos(Vec2(640.f, 503.f));
	AddObject(LAYER::DEFAULT, pImage);

	pImage = new CImage;
	pImage->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"Copyright", L"texture\\UI\\Copyright.png"));
	pImage->SetScaleToTex();
	pImage->SetPos(Vec2(640.f, 622.f));
	AddObject(LAYER::DEFAULT, pImage);

}

void CTitleLevel::enter()
{
}

void CTitleLevel::exit()
{
}

void CTitleLevel::tick()
{
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::MAINMENU_LEVEL);
	}

}
