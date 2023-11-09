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
	// init에서 해줘야 하는 것
	
	// 충돌 설정

	// 객체 생성
	// 위치 설정

	Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;

	// 몬스터 생성
	CMonster* pMonster = new CMonster;

	pMonster->SetPos(vLookAt);
	pMonster->SetScale(Vec2(100.f, 100.f));
	AddObject(LAYER::MONSTER, pMonster);

	pMonster = new CMonster;
	pMonster->SetPos(vLookAt + Vec2(150.f, 0.f));
	pMonster->SetScale(Vec2(100.f, 100.f));
	AddObject(LAYER::PLAYER, pMonster);



	// 충돌 설정
	CCollisionMgr::GetInst()->CheckCollision(LAYER::MONSTER, LAYER::PLAYER);
	CCollisionMgr::GetInst()->CheckCollision(LAYER::PLAYER_PJ, LAYER::MONSTER);
	CCollisionMgr::GetInst()->CheckCollision(LAYER::PLAYER, LAYER::PLATFORM);
	CCollisionMgr::GetInst()->CheckCollision(LAYER::PLAYER, LAYER::PORTAL);



    // 플랫폼 생성
	CPlatform* pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(vLookAt + Vec2(0.f, 200.f)));
	AddObject(LAYER::PLATFORM, pPlatform);



}

void CPlayLevel::enter()
{
	// enter에서 해줘야 하는 것들

	// 1. Penitent 가져오기
	// 2. 카메라 설정
	// 3. 배경 음악 설정


	// Penitent 생성
	//CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();
	//pPenitent->SetPos(Vec2(1000.f, 2000.f));
	//AddObject(LAYER::PLAYER, pPenitent);



	// 카메라 설정
	CCamera::GetInst()->InitLookAt(Vec2(1140.f, 2100.f));
	CCamera::GetInst()->SetLookAt(Vec2(1140.f, 2100.f));

	Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;

	CCamera::GetInst()->InitLookAt(vLookAt);
	CCamera::GetInst()->SetLookAt(vLookAt);
	CCamera::GetInst()->SetCameraLimit(Vec2(1280.f, 720.f));


	//CCamera::GetInst()->FadeIn(2.5f);
	//CCamera::GetInst()->FadeOut(2.5f);

	// 사운드 설정
	//CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"BGM_01", L"sound\\DM.wav");
	//pSound->SetVolume(100);
	//pSound->PlayToBGM();

	

	

}

void CPlayLevel::exit()
{
	// Player 빼주기

	PullOutObject(LAYER::PLAYER);

}

void CPlayLevel::tick()
{
	CLevel::tick();

	if (KEY_TAP(KEY::M))
	{
		CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"BGM_02", L"sound\\BGM_Stage1.wav");
		pSound->SetVolume(100);
		pSound->PlayToBGM();
	}

	if (KEY_TAP(KEY::N))
	{
		ChangeLevel(LEVEL_TYPE::STAGE01_1);
	}

}
