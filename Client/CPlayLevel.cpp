#include "pch.h"
#include "CPlayLevel.h"

#include "CEngine.h"

#include "CCollisionMgr.h"
#include "CKeyMgr.h"

#include "CPlatform.h"
#include "CPlayer.h"

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
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetPos(Vec2(500.f, 200.f));
	pPlayer->SetScale(Vec2(50.f, 50.f));
	AddObject(LAYER::PLAYER, pPlayer);

	//Monster 생성
   //CMonster* pMonster = new CMonster;
   //pMonster->SetPos(Vec2(1000.f, 500.f));
   //pMonster->SetScale(Vec2(100.f, 100.f));
   //m_pCurLevel->AddObject(LAYER::MONSTER, pMonster);

   // 플랫폼 생성
	CPlatform* pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(800.f, 700.f));
	AddObject(LAYER::PLATFORM, pPlatform);

}

void CPlayLevel::enter()
{
	init();
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
}
