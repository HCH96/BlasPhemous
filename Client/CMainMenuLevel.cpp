#include "pch.h"
#include "CMainMenuLevel.h"

#include "CEngine.h"
#include "CCamera.h"

#include "CAssetMgr.h"
#include "CKeyMgr.h"
#include "CCamera.h"

#include "CImage.h"
#include "CTexture.h"
#include "CSelectBtn.h"

void ExitCallBack();
void LevelChageCallBack();

CMainMenuLevel::CMainMenuLevel()
	: m_arrBtn{}
	, m_pCursorImg(nullptr)
	, m_iCur(0)
{
}

CMainMenuLevel::~CMainMenuLevel()
{
}

void CMainMenuLevel::ChangeCursorImg()
{
	Vec2 vPos = m_arrBtn[m_iCur]->GetPos();

	m_pCursorImg->SetPos({ 998.f, vPos.y });

}

void CMainMenuLevel::init()
{
	// Ä«¸Þ¶ó ¼³Á¤
	Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;

	CCamera::GetInst()->SetLookAt(vLookAt);


	// Object ¹èÄ¡
	
	// background
	CImage* pImage = new CImage;
	CAnimator* pAnimator = pImage->GetAnimator();
	pAnimator->LoadAnimation(L"animdata\\UI\\MainMenu\\MainMenuBackground.txt");
	pImage->SetPos(Vec2(640.f, 360.f));
	pAnimator->Play(L"MainMenuBackground", true);
	AddObject(LAYER::DEFAULT, pImage);

	// Crisanta
	pImage = new CImage;
	pAnimator = pImage->GetAnimator();
	pAnimator->LoadAnimation(L"animdata\\UI\\MainMenu\\Crisanta.txt");
	pImage->SetPos(Vec2(640.f, 360.f));
	pImage->SetScale(Vec2(2.f, 2.f));
	pAnimator->Play(L"Crisanta", true);
	AddObject(LAYER::DEFAULT, pImage);

	// Å« ²ÉÀÙ
	pImage = new CImage;
	pAnimator = pImage->GetAnimator();
	pAnimator->LoadAnimation(L"animdata\\UI\\MainMenu\\Crisanta_BigPetal.txt");
	pImage->SetPos(Vec2(640.f, 360.f));
	pAnimator->Play(L"Crisanta_BigPetal", true);
	AddObject(LAYER::DEFAULT, pImage);

	// ²ÉÀÙ
	pImage = new CImage;
	pAnimator = pImage->GetAnimator();
	pAnimator->LoadAnimation(L"animdata\\UI\\MainMenu\\Crisanta_Petal.txt");
	pImage->SetPos(Vec2(640.f, 360.f));
	pAnimator->Play(L"Crisanta_Petal", true);
	AddObject(LAYER::DEFAULT, pImage);


	// ¾Æ±â
	m_pCursorImg = new CImage;
	pAnimator = m_pCursorImg->GetAnimator();
	pAnimator->LoadAnimation(L"animdata\\UI\\MainMenu\\alliedCherub.txt");
	m_pCursorImg->SetScale(Vec2(2.f, 2.f));
	m_pCursorImg->SetPos(Vec2(640.f, 360.f));
	pAnimator->Play(L"alliedCherub", true);
	AddObject(LAYER::DEFAULT, m_pCursorImg);



	// ¹öÆ° ÃÊ±âÈ­
	CAssetMgr::GetInst()->LoadTexture(L"Pilgrimage", L"texture\\UI\\MainMenu\\Pilgrimage.png");
	CAssetMgr::GetInst()->LoadTexture(L"Pilgrimage_Select", L"texture\\UI\\MainMenu\\Pilgrimage_Select.png");
	CAssetMgr::GetInst()->LoadTexture(L"Option", L"texture\\UI\\MainMenu\\Option.png");
	CAssetMgr::GetInst()->LoadTexture(L"Option_Select", L"texture\\UI\\MainMenu\\Option_Select.png");
	CAssetMgr::GetInst()->LoadTexture(L"Exit", L"texture\\UI\\MainMenu\\Exit.png");
	CAssetMgr::GetInst()->LoadTexture(L"Exit_Select", L"texture\\UI\\MainMenu\\Exit_Select.png");

	// ¼ø·Ê
	CSelectBtn* pBtn = new CSelectBtn;
	pBtn->SetNormalImg(L"Pilgrimage");
	pBtn->SetSelectImg(L"Pilgrimage_Select");
	pBtn->SetCallBack(LevelChageCallBack);
	pBtn->SetPos(Vec2(1100.f, 500.f));	
	pBtn->SetScale(Vec2(65.f, 30.f));
	AddObject(LAYER::UI, pBtn);

	m_arrBtn[(UINT)MAIN_MENU::PILGRIMAGE] = pBtn;


	pBtn = new CSelectBtn;
	pBtn->SetNormalImg(L"Option");
	pBtn->SetSelectImg(L"Option_Select");
	pBtn->SetPos(Vec2(1098.f, 550.f));
	pBtn->SetScale(Vec2(62.f, 30.f));
	AddObject(LAYER::UI, pBtn);

	m_arrBtn[(UINT)MAIN_MENU::OPTION] = pBtn;


	pBtn = new CSelectBtn;
	pBtn->SetNormalImg(L"Exit");
	pBtn->SetSelectImg(L"Exit_Select");
	pBtn->SetCallBack(ExitCallBack);
	pBtn->SetPos(Vec2(1117.f, 600.f));
	pBtn->SetScale(Vec2(96.f, 30.f));
	AddObject(LAYER::UI, pBtn);

	m_arrBtn[(UINT)MAIN_MENU::EXIT] = pBtn;

	m_arrBtn[m_iCur]->SetSelect(true);
	ChangeCursorImg();

}

void CMainMenuLevel::enter()
{
	CCamera::GetInst()->FadeIn(1.f);

}

void CMainMenuLevel::exit()
{
}

void CMainMenuLevel::tick()
{
	if (KEY_TAP(KEY::DOWN))
	{
		m_arrBtn[m_iCur]->SetSelect(false);
		++m_iCur;
		if (m_iCur >= (UINT)MAIN_MENU::END)
		{
			m_iCur = (UINT)MAIN_MENU::EXIT;
		}
		m_arrBtn[m_iCur]->SetSelect(true);
		ChangeCursorImg();
	}

	if (KEY_TAP(KEY::UP))
	{
		m_arrBtn[m_iCur]->SetSelect(false);
		--m_iCur;
		if (m_iCur < 0)
		{
			m_iCur = 0;
		}
		m_arrBtn[m_iCur]->SetSelect(true);
		ChangeCursorImg();
	}

	if (KEY_TAP(KEY::ENTER))
	{
		CSelectBtn* pBtn = m_arrBtn[m_iCur];
		pBtn->Select();
	}

	CLevel::tick();
}

void LevelChageCallBack()
{
	::ChangeLevel(LEVEL_TYPE::TEST_LEVEL);
}

void ExitCallBack()
{
	DestroyWindow(CEngine::GetInst()->GetMainWind());
}