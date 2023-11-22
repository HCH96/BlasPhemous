#include "pch.h"
#include "CTitleLevel.h"

#include "CEngine.h"

#include "CAssetMgr.h"
#include "CCollisionMgr.h"
#include "CCamera.h"
#include "CKeyMgr.h"

#include "CImage.h"

void CTitleLevel::init()
{
	// ī�޶� ����
	Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;

	CCamera::GetInst()->SetLookAt(vLookAt);

	CImage* pImage = new CImage;
	pImage->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"BlackBackground", L"texture\\UI\\BlackBackground.png"));
	pImage->SetScaleToTex();
	pImage->SetPos(Vec2(640.f, 360.f));
	AddObject(LAYER::DEFAULT, pImage);


	pImage = new CImage;
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

	// �浹 ����
	CCollisionMgr::GetInst()->CheckCollision(LAYER::PLAYER, LAYER::PLATFORM);
	CCollisionMgr::GetInst()->CheckCollision(LAYER::PLAYER, LAYER::MONSTER);
	CCollisionMgr::GetInst()->CheckCollision(LAYER::PLAYER, LAYER::MAP_OBJECT);
	CCollisionMgr::GetInst()->CheckCollision(LAYER::PLAYER, LAYER::LADDER);
	CCollisionMgr::GetInst()->CheckCollision(LAYER::PLAYER, LAYER::MONSTER_PJ);
	CCollisionMgr::GetInst()->CheckCollision(LAYER::PLAYER, LAYER::PROJECTILE);
	CCollisionMgr::GetInst()->CheckCollision(LAYER::PLAYER, LAYER::STATIC_MONSTER);

	CCollisionMgr::GetInst()->CheckCollision(LAYER::MONSTER, LAYER::PLATFORM);
	CCollisionMgr::GetInst()->CheckCollision(LAYER::SPAWNER, LAYER::PLATFORM);
	CCollisionMgr::GetInst()->CheckCollision(LAYER::PROJECTILE, LAYER::PLATFORM);


}

void CTitleLevel::enter()
{
	// Sound ���� 
	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"Relic", L"sound\\KeyEvents\\Relic.wav");

	pSound = CAssetMgr::GetInst()->LoadSound(L"Bridge", L"sound\\BGM\\Bridge.wav");
	pSound->PlayToBGM(true);

}

void CTitleLevel::exit()
{
}

void CTitleLevel::tick()
{
	if (KEY_TAP(KEY::ENTER))
	{
		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"Relic", L"sound\\KeyEvents\\Relic.wav");
		pSound->Play();

		CCamera::GetInst()->FadeOut(1.f, LEVEL_TYPE::MAINMENU_LEVEL);
	}

}
