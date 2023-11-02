#include "pch.h"
#include "CPlayLevel.h"

#include "CEngine.h"

#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include "CAssetMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"

#include "CPlatform.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CPenitent.h"


void CPlayLevel::init()
{

	// 카메라 설정
	Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;

	CCamera::GetInst()->SetLookAt(vLookAt);

	// 충돌 설정
	CCollisionMgr::GetInst()->CheckCollision(LAYER::MONSTER, LAYER::PLAYER);
	CCollisionMgr::GetInst()->CheckCollision(LAYER::PLAYER_PJ, LAYER::MONSTER);
	CCollisionMgr::GetInst()->CheckCollision(LAYER::PLAYER, LAYER::PLATFORM);


	// Plyaer 생성
	//CPlayer* pPlayer = new CPlayer;
	//pPlayer->SetPos(Vec2(500.f, 200.f));
	////pPlayer->SetScale(Vec2(50.f, 50.f));
	//AddObject(LAYER::PLAYER, pPlayer);

	// Penitent 생성
	CPenitent* pPenitent = new CPenitent;
	pPenitent->SetPos(Vec2(500.f, 200.f));
	AddObject(LAYER::PLAYER, pPenitent);

	//Monster 생성
	CMonster* pMonster = new CMonster;
	pMonster->SetPos(Vec2(1000.f, 500.f));
	pMonster->SetScale(Vec2(100.f, 100.f));
	AddObject(LAYER::MONSTER, pMonster);

    // 플랫폼 생성
	CPlatform* pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(800.f, 700.f));
	AddObject(LAYER::PLATFORM, pPlatform);



}

void CPlayLevel::enter()
{
	//CCamera::GetInst()->FadeIn(2.5f);
	//CCamera::GetInst()->FadeOut(2.5f);

	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"BGM_01", L"sound\\DM.wav");
	pSound->SetVolume(100);
	pSound->PlayToBGM();
}

void CPlayLevel::exit()
{
	DeleteAllObjects();
}

void CPlayLevel::tick()
{
	CLevel::tick();

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::EDITOR_LEVEL);
	}

	if (KEY_TAP(KEY::M))
	{
		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"BGM_02", L"sound\\BGM_Stage1.wav");
		pSound->SetVolume(100);
		pSound->PlayToBGM();
	}

}
