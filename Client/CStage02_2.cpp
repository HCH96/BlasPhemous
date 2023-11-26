#include "pch.h"
#include "CStage02_2.h"

#include "CEngine.h"

#include "CAssetMgr.h"

#include "CBackground.h"

#include "CPenitent.h"
#include "CPlatform.h"
#include "CPenitentUI.h"
#include "CTearsUI.h"

#include "CBossPanel.h"

#include "CPope.h"

#include "CFirebolt.h"
#include "CFireboltSpawner.h"

#include "CMagicMissile.h"
#include "CMagicMissileSpawner.h"

#include "CToxic.h"
#include "CToxicSpawner.h"

#include "CLightning.h"
#include "CLightningSpawner.h"

#include "CKeyMgr.h"

#include "CBossIntro.h"
#include "CWall.h"

void CStage02_2::BossIntro()
{
	// Penitent State ����
	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();
	CStateMachine* pSM = pPenitent->GetComponent<CStateMachine>();
	pSM->ChangeState((UINT)PENITENT_STATE::INTRO);

	// Camera ����
	CCamera::GetInst()->SetTarget(nullptr);
	CCamera::GetInst()->SetSpeed(400.f);
	CCamera::GetInst()->SetLookAt(Vec2(2280.f,1520.f));
	//CCamera::GetInst()->SetLookAtOffsetY(0.f);


	// ElderBrother shadow Animation ���
	CObj* pBoss = GetBoss();

	CStateMachine* p_AI = pBoss->GetComponent<CStateMachine>();
	p_AI->ChangeState((UINT)POPE::INTRO);

}

void CStage02_2::IntroEnd()
{
	// �� ����
	m_pLeftWall->SetPos(Vec2(1600.f, 1520.f));
	m_pRightWall->SetPos(Vec2(2960.f, 1520.f));

	// Camera Limit 
	CCamera::GetInst()->SetCameraLimitLT(Vec2(1640.f, 580.f * 2.f));
	CCamera::GetInst()->SetCameraLimit(Vec2(2920.f, 940.f * 2.f));


	// Sound
	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"Pontiff", L"sound\\BossMusic\\Pontiff.wav");
	pSound->PlayToBGM();

	// Penitent State ����
	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();
	CStateMachine* pSM = pPenitent->GetComponent<CStateMachine>();
	pSM->ChangeState((UINT)PENITENT_STATE::IDLE);


	// Boss HP UI ǥ��
	const vector<CObj*> vecUI = CLevelMgr::GetInst()->GetCurLevel()->GetObjects(LAYER::UI);
	for (int i = 0; i < vecUI.size(); ++i)
	{
		if (vecUI[i]->GetName() == L"BossPanel")
		{
			CBossPanel* pPanel = dynamic_cast<CBossPanel*>(vecUI[i]);
			pPanel->On();
		}
	}
}

void CStage02_2::BossDeath()
{
	::ChangeLevel(LEVEL_TYPE::STAGE02_3);
}

void CStage02_2::init()
{
	//Background 0
	CBackground* pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"12_2_BeforeParallax_0", L"texture\\Map\\DeambulatoryOfHisHoliness\\12-2\\12_2_BeforeParallax_0.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	pBackGround->SetPos(Vec2(0.f, 200.f));
	pBackGround->SetParallaxSpeed(Vec2(0.5f, 1.f));
	AddObject(LAYER::BACKGROUND, pBackGround);


	// Tile 
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"12_2_Tile", L"texture\\Map\\DeambulatoryOfHisHoliness\\12-2\\12_2_Tile.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::TILE, pBackGround);

	// Foreground 1
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"12_2_AfterLayer", L"texture\\Map\\DeambulatoryOfHisHoliness\\12-2\\12_2_AfterLayer.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::TILE, pBackGround);


	CPlatform* pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(2250.f, 1740.f));
	pPlatform->SetScale(Vec2(4430.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);


	// Boss
	CPope* pPope = new CPope;
	pPope->SetPos(Vec2(0.f, 0.f));
	pPope->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::MONSTER, pPope);


	// Firebolt
	CFireboltSpawner* pFireSpawner = new CFireboltSpawner;
	AddObject(LAYER::SPAWNER, pFireSpawner);
	pPope->RegisterFireSpawner(pFireSpawner);


	CFirebolt* pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"PONTIFF_SPELL_FIRE", L"sound\\Object\\Monster\\Boss\\Pontiff\\PONTIFF_SPELL_FIRE.wav");
	pFirebolt->SetSound(pSound);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pSound = CAssetMgr::GetInst()->LoadSound(L"PONTIFF_SPELL_FIRE2", L"sound\\Object\\Monster\\Boss\\Pontiff\\PONTIFF_SPELL_FIRE.wav");
	pFirebolt->SetSound(pSound);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pSound = CAssetMgr::GetInst()->LoadSound(L"PONTIFF_SPELL_FIRE3", L"sound\\Object\\Monster\\Boss\\Pontiff\\PONTIFF_SPELL_FIRE.wav");
	pFirebolt->SetSound(pSound);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pSound = CAssetMgr::GetInst()->LoadSound(L"PONTIFF_SPELL_FIRE4", L"sound\\Object\\Monster\\Boss\\Pontiff\\PONTIFF_SPELL_FIRE.wav");
	pFirebolt->SetSound(pSound);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pSound = CAssetMgr::GetInst()->LoadSound(L"PONTIFF_SPELL_FIRE5", L"sound\\Object\\Monster\\Boss\\Pontiff\\PONTIFF_SPELL_FIRE.wav");
	pFirebolt->SetSound(pSound);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pSound = CAssetMgr::GetInst()->LoadSound(L"PONTIFF_SPELL_FIRE6", L"sound\\Object\\Monster\\Boss\\Pontiff\\PONTIFF_SPELL_FIRE.wav");
	pFirebolt->SetSound(pSound);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pSound = CAssetMgr::GetInst()->LoadSound(L"PONTIFF_SPELL_FIRE7", L"sound\\Object\\Monster\\Boss\\Pontiff\\PONTIFF_SPELL_FIRE.wav");
	pFirebolt->SetSound(pSound);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pSound = CAssetMgr::GetInst()->LoadSound(L"PONTIFF_SPELL_FIRE8", L"sound\\Object\\Monster\\Boss\\Pontiff\\PONTIFF_SPELL_FIRE.wav");
	pFirebolt->SetSound(pSound);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pSound = CAssetMgr::GetInst()->LoadSound(L"PONTIFF_SPELL_FIRE9", L"sound\\Object\\Monster\\Boss\\Pontiff\\PONTIFF_SPELL_FIRE.wav");
	pFirebolt->SetSound(pSound);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pSound = CAssetMgr::GetInst()->LoadSound(L"PONTIFF_SPELL_FIRE10", L"sound\\Object\\Monster\\Boss\\Pontiff\\PONTIFF_SPELL_FIRE.wav");
	pFirebolt->SetSound(pSound);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pSound = CAssetMgr::GetInst()->LoadSound(L"PONTIFF_SPELL_FIRE11", L"sound\\Object\\Monster\\Boss\\Pontiff\\PONTIFF_SPELL_FIRE.wav");
	pFirebolt->SetSound(pSound);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pSound = CAssetMgr::GetInst()->LoadSound(L"PONTIFF_SPELL_FIRE12", L"sound\\Object\\Monster\\Boss\\Pontiff\\PONTIFF_SPELL_FIRE.wav");
	pFirebolt->SetSound(pSound);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pSound = CAssetMgr::GetInst()->LoadSound(L"PONTIFF_SPELL_FIRE13", L"sound\\Object\\Monster\\Boss\\Pontiff\\PONTIFF_SPELL_FIRE.wav");
	pFirebolt->SetSound(pSound);

	// MagicMissile 
	CMagicMissileSpawner* pMagicMissileSpawner = new CMagicMissileSpawner;
	AddObject(LAYER::SPAWNER, pMagicMissileSpawner);
	pPope->RegisterMagicSpawner(pMagicMissileSpawner);

	CMagicMissile* pMagicMissile = new CMagicMissile;
	pMagicMissileSpawner->AddMagicMissile(pMagicMissile);
	AddObject(LAYER::PROJECTILE, pMagicMissile);

	pMagicMissile = new CMagicMissile;
	pMagicMissileSpawner->AddMagicMissile(pMagicMissile);
	AddObject(LAYER::PROJECTILE, pMagicMissile);

	pMagicMissile = new CMagicMissile;
	pMagicMissileSpawner->AddMagicMissile(pMagicMissile);
	AddObject(LAYER::PROJECTILE, pMagicMissile);

	pMagicMissile = new CMagicMissile;
	pMagicMissileSpawner->AddMagicMissile(pMagicMissile);
	AddObject(LAYER::PROJECTILE, pMagicMissile);

	pMagicMissile = new CMagicMissile;
	pMagicMissileSpawner->AddMagicMissile(pMagicMissile);
	AddObject(LAYER::PROJECTILE, pMagicMissile);

	pMagicMissile = new CMagicMissile;
	pMagicMissileSpawner->AddMagicMissile(pMagicMissile);
	AddObject(LAYER::PROJECTILE, pMagicMissile);

	pMagicMissile = new CMagicMissile;
	pMagicMissileSpawner->AddMagicMissile(pMagicMissile);
	AddObject(LAYER::PROJECTILE, pMagicMissile);

	pMagicMissile = new CMagicMissile;
	pMagicMissileSpawner->AddMagicMissile(pMagicMissile);
	AddObject(LAYER::PROJECTILE, pMagicMissile);

	// Toxic

	CToxicSpawner* pToxicSpawner = new CToxicSpawner;
	AddObject(LAYER::SPAWNER, pToxicSpawner);
	pPope->RegisterToxicSpawner(pToxicSpawner);

	CToxic* pToxic = new CToxic;
	pToxicSpawner->AddToxic(pToxic);
	AddObject(LAYER::PROJECTILE, pToxic);

	pToxic = new CToxic;
	pToxicSpawner->AddToxic(pToxic);
	AddObject(LAYER::PROJECTILE, pToxic);

	pToxic = new CToxic;
	pToxicSpawner->AddToxic(pToxic);
	AddObject(LAYER::PROJECTILE, pToxic);

	pToxic = new CToxic;
	pToxicSpawner->AddToxic(pToxic);
	AddObject(LAYER::PROJECTILE, pToxic);

	pToxic = new CToxic;
	pToxicSpawner->AddToxic(pToxic);
	AddObject(LAYER::PROJECTILE, pToxic);

	pToxic = new CToxic;
	pToxicSpawner->AddToxic(pToxic);
	AddObject(LAYER::PROJECTILE, pToxic);

	pToxic = new CToxic;
	pToxicSpawner->AddToxic(pToxic);
	AddObject(LAYER::PROJECTILE, pToxic);

	pToxic = new CToxic;
	pToxicSpawner->AddToxic(pToxic);
	AddObject(LAYER::PROJECTILE, pToxic);

	pToxic = new CToxic;
	pToxicSpawner->AddToxic(pToxic);
	AddObject(LAYER::PROJECTILE, pToxic);

	pToxic = new CToxic;
	pToxicSpawner->AddToxic(pToxic);
	AddObject(LAYER::PROJECTILE, pToxic);

	// Lightning
	CLightningSpawner* pLightningSpawner = new CLightningSpawner;
	AddObject(LAYER::SPAWNER, pLightningSpawner);
	pPope->RegisterLightningSpawner(pLightningSpawner);

	CLightning* pLightning = new CLightning;
	pLightningSpawner->AddLightning(pLightning);
	AddObject(LAYER::PROJECTILE, pLightning);

	pSound = CAssetMgr::GetInst()->LoadSound(L"THUNDER_SPELL1", L"sound\\Object\\Monster\\Boss\\Pontiff\\THUNDER_SPELL.wav");
	pLightning->SetSound(pSound);

	pLightning = new CLightning;
	pLightningSpawner->AddLightning(pLightning);
	AddObject(LAYER::PROJECTILE, pLightning);

	pSound = CAssetMgr::GetInst()->LoadSound(L"THUNDER_SPELL2", L"sound\\Object\\Monster\\Boss\\Pontiff\\THUNDER_SPELL.wav");
	pLightning->SetSound(pSound);

	pLightning = new CLightning;
	pLightningSpawner->AddLightning(pLightning);
	AddObject(LAYER::PROJECTILE, pLightning);

	pSound = CAssetMgr::GetInst()->LoadSound(L"THUNDER_SPELL3", L"sound\\Object\\Monster\\Boss\\Pontiff\\THUNDER_SPELL.wav");
	pLightning->SetSound(pSound);

	pLightning = new CLightning;
	pLightningSpawner->AddLightning(pLightning);
	AddObject(LAYER::PROJECTILE, pLightning);

	pSound = CAssetMgr::GetInst()->LoadSound(L"THUNDER_SPELL4", L"sound\\Object\\Monster\\Boss\\Pontiff\\THUNDER_SPELL.wav");
	pLightning->SetSound(pSound);

	pLightning = new CLightning;
	pLightningSpawner->AddLightning(pLightning);
	AddObject(LAYER::PROJECTILE, pLightning);

	pSound = CAssetMgr::GetInst()->LoadSound(L"THUNDER_SPELL5", L"sound\\Object\\Monster\\Boss\\Pontiff\\THUNDER_SPELL.wav");
	pLightning->SetSound(pSound);

	pLightning = new CLightning;
	pLightningSpawner->AddLightning(pLightning);
	AddObject(LAYER::PROJECTILE, pLightning);

	pSound = CAssetMgr::GetInst()->LoadSound(L"THUNDER_SPELL6", L"sound\\Object\\Monster\\Boss\\Pontiff\\THUNDER_SPELL.wav");
	pLightning->SetSound(pSound);


	// Wall
	m_pLeftWall = new CWall;

	m_pLeftWall->SetPos(Vec2(0.f, 0.f));
	m_pLeftWall->SetScale(Vec2(50.f, 500.f));
	AddObject(LAYER::PLATFORM, m_pLeftWall);

	m_pRightWall = new CWall;

	m_pRightWall->SetPos(Vec2(0.f, 0.f));
	m_pRightWall->SetScale(Vec2(50.f, 500.f));
	AddObject(LAYER::PLATFORM, m_pRightWall);



	// UI ����
	CPenitentUI* pPenitentUI = new CPenitentUI;
	AddObject(LAYER::UI, pPenitentUI);

	CTearsUI* pTearsUI = new CTearsUI;
	AddObject(LAYER::UI, pTearsUI);

	RegisterBoss(pPope);

	CBossPanel* pBossPanel = new CBossPanel;
	AddObject(LAYER::UI, pBossPanel);
	pBossPanel->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"PopeName", L"texture\\UI\\PopeName.png"));

	// Boss Intro 
	CBossIntro* pBossIntro = new CBossIntro;
	pBossIntro->SetPos(Vec2(2050.f, 1640.f));
	AddObject(LAYER::BOSSINTRO, pBossIntro);


}

void CStage02_2::enter()
{
	//Penitent ����
	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();
	pPenitent->SetState(PENITENT_STATE::IDLE);
	pPenitent->SetPos(Vec2(240.f, 1740.f));
	pPenitent->SetLeft(false);
	if ((UINT)LEVEL_TYPE::STAGE02_1 == CLevelMgr::GetInst()->GetPrevLevel())
	{
		pPenitent->SetPos(Vec2(240.f, 1740.f));
	}

	if ((UINT)LEVEL_TYPE::STAGE02_3 == CLevelMgr::GetInst()->GetPrevLevel())
	{
		pPenitent->SetPos(Vec2(2264.f, 1740.f));
	}
	AddObject(LAYER::PLAYER, pPenitent);

	// ī�޶� ����
	CCamera::GetInst()->FadeIn(1.f);
	CCamera::GetInst()->SetLookAtOffsetY(-50.f);
	CCamera::GetInst()->InitLookAt(pPenitent->GetPos());
	CCamera::GetInst()->SetTarget(pPenitent);
	CCamera::GetInst()->SetCameraLimitLT(Vec2(90.f * 2.f, 580.f * 2.f));
	CCamera::GetInst()->SetCameraLimit(Vec2(2030.f * 2.f, 940.f * 2.f));

	// Sound

	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"Final Boss Wind", L"sound\\BossMusic\\Final Boss Wind.wav");
	pSound->PlayToBGM();
}

void CStage02_2::exit()
{
	PullOutObject(LAYER::PLAYER);

}

void CStage02_2::tick()
{
	CLevel::tick();

}
