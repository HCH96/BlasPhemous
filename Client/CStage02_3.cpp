#include "pch.h"
#include "CStage02_3.h"

#include "CEngine.h"

#include "CAssetMgr.h"

#include "CBackground.h"

#include "CPenitent.h"
#include "CPlatform.h"
#include "CPenitentUI.h"
#include "CTearsUI.h"

#include "CWall.h"
#include "CTwisterBackground.h"
#include "CAshPlatform.h"

#include "CGiantSword.h"
#include "Pontiff.h"

#include "CToxic.h"
#include "CToxicSpawner.h"

#include "CFirebolt.h"
#include "CFireboltSpawner.h"

#include "CMagicMissile.h"
#include "CMagicMissileSpawner2.h"

#include "CLightning.h"
#include "CLightningSpawner2.h"

#include "CBossPanel.h"

#include "CAshCloud.h"


void CStage02_3::BossDeath()
{
	// Boss UI Off
	const vector<CObj*> vecUI = CLevelMgr::GetInst()->GetCurLevel()->GetObjects(LAYER::UI);
	for (int i = 0; i < vecUI.size(); ++i)
	{
		if (vecUI[i]->GetName() == L"BossPanel")
		{
			CBossPanel* pPanel = dynamic_cast<CBossPanel*>(vecUI[i]);
			pPanel->Off();
		}
	}

	// BGM 변경
	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"Boss_Fight_Ending", L"sound\\KeyEvents\\Boss_Fight_Ending.wav");
	pSound->PlayToBGM();

	// Boss Clear Screen
	CCamera::GetInst()->BossClear(1.f);

}

void CStage02_3::init()
{
	//Background 0
	CBackground* pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"12_3_BeforeLayer_0", L"texture\\Map\\DeambulatoryOfHisHoliness\\12-3\\12_3_BeforeLayer_0.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::BACKGROUND, pBackGround);

	//Background 1
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"12_3_BeforeLayer_1", L"texture\\Map\\DeambulatoryOfHisHoliness\\12-3\\12_3_BeforeLayer_1.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::BACKGROUND, pBackGround);

	// TwisterBackground

	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"Twister", L"texture\\Effect\\pontif-twister-background.png");
	CTwisterBackground* pTwister = new CTwisterBackground;
	pTwister->SetPos(Vec2(0.f, 0.f));
	pTwister->SetTexture(pTex);
	pTwister->SetAlpha(50.f);
	pTwister->SetMaxAlpha(100.f);
	pTwister->SetMinAlpha(30.f);
	AddObject(LAYER::BACKGROUND, pTwister);

	pTex = CAssetMgr::GetInst()->LoadTexture(L"Twister_Fore", L"texture\\Effect\\pontif-twister-foreground.png");
	pTwister = new CTwisterBackground;
	pTwister->SetPos(Vec2(480.f, 0.f));
	pTwister->SetTexture(pTex);
	pTwister->SetAlpha(255.f);
	pTwister->SetMaxAlpha(255.f);
	pTwister->SetMinAlpha(255.f);
	AddObject(LAYER::FOREGROUND, pTwister);


	// Tile 
	pBackGround = new CBackground;
	pBackGround->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"12_3_Tile", L"texture\\Map\\DeambulatoryOfHisHoliness\\12-3\\12_3_Tile.png"));
	pBackGround->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::TILE, pBackGround);


	// Platform
	CPlatform* pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(1340.f, 1000.f));
	pPlatform->SetScale(Vec2(2200.f, 50.f));
	AddObject(LAYER::PLATFORM, pPlatform);

	CWall* pWall = new CWall;
	pWall->SetPos(Vec2(670.f, 700.f));
	pWall->SetScale(Vec2(30.f, 1000.f));
	AddObject(LAYER::PLATFORM, pWall);

	pWall = new CWall;
	pWall->SetPos(Vec2(2010.f, 700.f));
	pWall->SetScale(Vec2(30.f, 1000.f));
	AddObject(LAYER::PLATFORM, pWall);

	// 1번 그룹
	CAshPlatform* pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(780.f, 700.f));
	pAshPlatform->SetAcc(12.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);

	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(1900.f, 700.f));
	pAshPlatform->SetAcc(12.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);

	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(920.f, 850.f));
	pAshPlatform->SetAcc(12.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);

	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(1760.f, 850.f));
	pAshPlatform->SetAcc(12.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);

	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(1060.f, 700.f));
	pAshPlatform->SetAcc(12.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);

	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(1620.f, 700.f));
	pAshPlatform->SetAcc(12.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);

	// 2번 그룹
	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(780.f, 850.f));
	pAshPlatform->SetAcc(8.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);

	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(1900.f, 850.f));
	pAshPlatform->SetAcc(8.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);

	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(1200.f, 700.f));
	pAshPlatform->SetAcc(8.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);

	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(1480.f, 700.f));
	pAshPlatform->SetAcc(8.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);

	// 3번 그룹
	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(920.f, 700.f));
	pAshPlatform->SetAcc(4.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);

	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(1760.f, 700.f));
	pAshPlatform->SetAcc(4.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);

	// 4번 그룹
	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(1060.f, 850.f));
	pAshPlatform->SetAcc(0.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);

	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(1620.f, 850.f));
	pAshPlatform->SetAcc(0.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);


	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(1200.f, 775.f));
	pAshPlatform->SetAcc(0.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);

	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(1480.f, 775.f));
	pAshPlatform->SetAcc(0.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);


	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(1200.f, 575.f));
	pAshPlatform->SetAcc(6.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);

	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(1480.f, 575.f));
	pAshPlatform->SetAcc(6.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);


	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(1620.f, 500.f));
	pAshPlatform->SetAcc(6.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);

	pAshPlatform = new CAshPlatform;
	pAshPlatform->SetPos(Vec2(1060.f, 500.f));
	pAshPlatform->SetAcc(6.f);
	AddObject(LAYER::PLATFORM, pAshPlatform);


	// Boss
	Pontiff* pPontiff = new Pontiff;
	pPontiff->SetPos(Vec2(1340.f, 1000.f));
	AddObject(LAYER::STATIC_MONSTER, pPontiff);


	CGiantSword* pSword = new CGiantSword;
	pSword->SetPos(Vec2(1480.f, 850.f));
	AddObject(LAYER::MONSTER, pSword);

	// Pattern

	// Toxic
	CToxicSpawner* pToxicSpawner = new CToxicSpawner;
	AddObject(LAYER::SPAWNER, pToxicSpawner);
	pPontiff->RegisterToxicSpawner(pToxicSpawner);

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

	// Firebolt 1
	CFireboltSpawner* pFireSpawner = new CFireboltSpawner;
	AddObject(LAYER::SPAWNER, pFireSpawner);
	pPontiff->RegisterFireSpawner(pFireSpawner);


	CFirebolt* pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"PONTIFF_SPELL_FIRE", L"sound\\Object\\Monster\\Boss\\Pontiff\\PONTIFF_SPELL_FIRE.wav");
	pFirebolt->SetSound(pSound);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pSound = CAssetMgr::GetInst()->LoadSound(L"PONTIFF_SPELL_FIRE1", L"sound\\Object\\Monster\\Boss\\Pontiff\\PONTIFF_SPELL_FIRE.wav");
	pFirebolt->SetSound(pSound);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pSound = CAssetMgr::GetInst()->LoadSound(L"PONTIFF_SPELL_FIRE2", L"sound\\Object\\Monster\\Boss\\Pontiff\\PONTIFF_SPELL_FIRE.wav");
	pFirebolt->SetSound(pSound);


	// Firebolt 2
	pFireSpawner = new CFireboltSpawner;
	AddObject(LAYER::SPAWNER, pFireSpawner);
	pPontiff->RegisterFireSpawner(pFireSpawner);


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


	// Firebolt 3
	pFireSpawner = new CFireboltSpawner;
	AddObject(LAYER::SPAWNER, pFireSpawner);
	pPontiff->RegisterFireSpawner(pFireSpawner);


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


	// Firebolt 4
	pFireSpawner = new CFireboltSpawner;
	AddObject(LAYER::SPAWNER, pFireSpawner);
	pPontiff->RegisterFireSpawner(pFireSpawner);


	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pSound = CAssetMgr::GetInst()->LoadSound(L"PONTIFF_SPELL_FIRE9", L"sound\\Object\\Monster\\Boss\\Pontiff\\PONTIFF_SPELL_FIRE.wav");
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


	// Firebolt 5
	pFireSpawner = new CFireboltSpawner;
	AddObject(LAYER::SPAWNER, pFireSpawner);
	pPontiff->RegisterFireSpawner(pFireSpawner);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pSound = CAssetMgr::GetInst()->LoadSound(L"PONTIFF_SPELL_FIRE13", L"sound\\Object\\Monster\\Boss\\Pontiff\\PONTIFF_SPELL_FIRE.wav");
	pFirebolt->SetSound(pSound);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pSound = CAssetMgr::GetInst()->LoadSound(L"PONTIFF_SPELL_FIRE14", L"sound\\Object\\Monster\\Boss\\Pontiff\\PONTIFF_SPELL_FIRE.wav");
	pFirebolt->SetSound(pSound);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pSound = CAssetMgr::GetInst()->LoadSound(L"PONTIFF_SPELL_FIRE15", L"sound\\Object\\Monster\\Boss\\Pontiff\\PONTIFF_SPELL_FIRE.wav");
	pFirebolt->SetSound(pSound);


	// Firebolt 6
	pFireSpawner = new CFireboltSpawner;
	AddObject(LAYER::SPAWNER, pFireSpawner);
	pPontiff->RegisterFireSpawner(pFireSpawner);


	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pSound = CAssetMgr::GetInst()->LoadSound(L"PONTIFF_SPELL_FIRE21", L"sound\\Object\\Monster\\Boss\\Pontiff\\PONTIFF_SPELL_FIRE.wav");
	pFirebolt->SetSound(pSound);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pSound = CAssetMgr::GetInst()->LoadSound(L"PONTIFF_SPELL_FIRE22", L"sound\\Object\\Monster\\Boss\\Pontiff\\PONTIFF_SPELL_FIRE.wav");
	pFirebolt->SetSound(pSound);

	pFirebolt = new CFirebolt;
	pFireSpawner->AddFirebolt(pFirebolt);
	AddObject(LAYER::PROJECTILE, pFirebolt);

	pSound = CAssetMgr::GetInst()->LoadSound(L"PONTIFF_SPELL_FIRE23", L"sound\\Object\\Monster\\Boss\\Pontiff\\PONTIFF_SPELL_FIRE.wav");
	pFirebolt->SetSound(pSound);

	// MagicMissile 1
	CMagicMissileSpawner2* pMagicMissileSpawner = new CMagicMissileSpawner2;
	AddObject(LAYER::SPAWNER, pMagicMissileSpawner);
	pPontiff->RegisterMagicSpawner(pMagicMissileSpawner);

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

	// MagicMissile 1
	pMagicMissileSpawner = new CMagicMissileSpawner2;
	AddObject(LAYER::SPAWNER, pMagicMissileSpawner);
	pPontiff->RegisterMagicSpawner(pMagicMissileSpawner);

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

	// Lightning
	CLightningSpawner2* pLightningSpawner = new CLightningSpawner2;
	AddObject(LAYER::SPAWNER, pLightningSpawner);
	pPontiff->RegisterLightningSpawner(pLightningSpawner);

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



	CAshCloud* pCloud = new CAshCloud;
	pCloud->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"ash-clouds_0", L"texture\\Effect\\ash-clouds_0.png"));
	pCloud->SetPos(Vec2(940.f, 1020.f));
	pCloud->SetDir(true);
	AddObject(LAYER::WORLD_STATIC, pCloud);


	pCloud = new CAshCloud;
	pCloud->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"ash-clouds_1", L"texture\\Effect\\ash-clouds_1.png"));
	pCloud->SetPos(Vec2(1740.f, 1020.f));
	pCloud->SetDir(false);

	AddObject(LAYER::WORLD_STATIC, pCloud);


	// Register 
	pPontiff->RegisterSword(pSword);
	pSword->registerPontiff(pPontiff);

	RegisterBoss(pPontiff);

	CBossPanel* pBossPanel = new CBossPanel;
	AddObject(LAYER::UI, pBossPanel);
	pBossPanel->SetTexture(CAssetMgr::GetInst()->LoadTexture(L"PontiffName", L"texture\\UI\\Pontiff.png"));
	pBossPanel->On();

	// UI 
	CPenitentUI* pPenitentUI = new CPenitentUI;
	AddObject(LAYER::UI, pPenitentUI);

	CTearsUI* pTearsUI = new CTearsUI;
	AddObject(LAYER::UI, pTearsUI);



}

void CStage02_3::enter()
{
	//Penitent 생성
	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();
	pPenitent->SetState(PENITENT_STATE::IDLE);
	pPenitent->SetPos(Vec2(1370.f, 1000.f));
	pPenitent->SetLeft(false);

	AddObject(LAYER::PLAYER, pPenitent);

	// 카메라 설정
	CCamera::GetInst()->FadeIn(1.f);
	CCamera::GetInst()->InitLookAt(pPenitent->GetPos());
	CCamera::GetInst()->SetCameraLimitLT(Vec2(350.f * 2.f, 150.f * 2.f));
	CCamera::GetInst()->SetCameraLimit(Vec2(990.f * 2.f, 510.f * 2.f));

	// Sound
	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"Pontiff", L"sound\\BossMusic\\Pontiff.wav");
	pSound->SetVolume(15.f);
	pSound->PlayToBGM(true);
}

void CStage02_3::exit()
{
}

void CStage02_3::tick()
{
	CLevel::tick();
}
