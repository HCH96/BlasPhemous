#include "pch.h"
#include "CPlayLevel.h"

#include "CEngine.h"

#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include "CAssetMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"

#include "CPlatform.h"
#include "CWall.h"
#include "CLedge.h"
#include "CPenitent.h"
#include "CLadder.h"



#include "CPenitentUI.h"
#include "CTearsUI.h"



void CPlayLevel::init()
{
	// init���� ����� �ϴ� ��
	
	// �浹 ����

	// ��ü ����
	// ��ġ ����

	Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;

	// ���� ����
	//CMonster* pMonster = new CMonster;

	//pMonster->SetPos(vLookAt);
	//pMonster->SetScale(Vec2(100.f, 100.f));
	//AddObject(LAYER::MONSTER, pMonster);

	//pMonster = new CMonster;
	//pMonster->SetPos(vLookAt + Vec2(150.f, 0.f));
	//pMonster->SetScale(Vec2(100.f, 100.f));
	//AddObject(LAYER::PLAYER, pMonster);







    // �÷��� ����
	CPlatform* pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(640.f, 150.f));
	pPlatform->SetScale(Vec2(1000.f, 30.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(640.f, 650.f));
	pPlatform->SetScale(Vec2(1000.f, 30.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	CLedge* pLedge = new CLedge;
	pLedge->SetPos(Vec2(840.f, 400.f));
	pLedge->SetScale(Vec2(100.f, 30.f));
	AddObject(LAYER::PLATFORM, pLedge);

	CLadder* pLadder = new CLadder;
	pLadder->SetPos(Vec2(440.f, 350.f));
	pLadder->SetScale(Vec2(50.f, 400.f));
	AddObject(LAYER::PLATFORM, pLadder);


	//pPlatform = new CPlatform;
	//pPlatform->SetPos(Vec2(640.f, 700.f));
	//pPlatform->SetScale(Vec2(1000.f, 30.f));
	//AddObject(LAYER::PLATFORM, pPlatform);
	//
	//CWall* pWall = new CWall;
	//pWall->SetPos(Vec2(240.f, 500.f));
	//pWall->SetScale(Vec2(20.f, 1000.f));
	//AddObject(LAYER::PLATFORM, pWall);

	// UI ����
	CPenitentUI* pPenitentUI = new CPenitentUI;
	AddObject(LAYER::UI, pPenitentUI);

	CTearsUI* pTearsUI = new CTearsUI;
	AddObject(LAYER::UI, pTearsUI);
}

void CPlayLevel::enter()
{
	// enter���� ����� �ϴ� �͵�

	// 1. Penitent ��������
	// 2. ī�޶� ����
	// 3. ��� ���� ����


	// Penitent ����
	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();
	pPenitent->SetState(PENITENT_STATE::FALL);
	pPenitent->SetPos(Vec2(640.f, 360.f));
	AddObject(LAYER::PLAYER, pPenitent);



	// ī�޶� ����
	Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;

	CCamera::GetInst()->InitLookAt(vLookAt);
	CCamera::GetInst()->SetLookAt(vLookAt);
	CCamera::GetInst()->SetCameraLimit(Vec2(1280.f, 720.f));


	//CCamera::GetInst()->FadeIn(2.5f);
	//CCamera::GetInst()->FadeOut(2.5f);

	// ���� ����
	//CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"BGM_01", L"sound\\DM.wav");
	//pSound->SetVolume(100);
	//pSound->PlayToBGM();

	

	

}

void CPlayLevel::exit()
{
	// Player ���ֱ�

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
