#include "pch.h"
#include "CLevelMgr.h"

#include "CPlayLevel.h"

#include "CTitleLevel.h"
#include "CMainMenuLevel.h"
#include "CStage01_1.h"


#include "CPenitent.h"

CLevelMgr::CLevelMgr()
	: m_pCurLevel(nullptr)
	, m_arrLevels{}
	, m_pPenitent(nullptr)
{}


CLevelMgr::~CLevelMgr()
{
	for (UINT i = 0; i < (UINT)LEVEL_TYPE::END; ++i)
	{
		if (nullptr != m_arrLevels[i])
		{
			delete m_arrLevels[i];
			m_arrLevels[i] = nullptr;
		}
	}

}

void CLevelMgr::ChangeLevel(LEVEL_TYPE _eType)
{
	if (m_pCurLevel == m_arrLevels[(UINT)_eType])
		return;

	if (nullptr != m_pCurLevel)
		m_pCurLevel->exit();

	m_pCurLevel = m_arrLevels[(UINT)_eType];

	m_pCurLevel->enter();
	m_pCurLevel->begin();

}

void CLevelMgr::init()
{
	// Penitent �����͸� ���
	CPenitent* pPenitent = new CPenitent;
	m_pPenitent = pPenitent;

	// ��� ���� ����
	m_arrLevels[(UINT)LEVEL_TYPE::TEST_LEVEL] = new CPlayLevel;
	m_arrLevels[(UINT)LEVEL_TYPE::TITLE_LEVEL] = new CTitleLevel;
	m_arrLevels[(UINT)LEVEL_TYPE::MAINMENU_LEVEL] = new CMainMenuLevel;
	m_arrLevels[(UINT)LEVEL_TYPE::STAGE01_1] = new CStage01_1;

	// ���� �ʱ�ȭ
	for (UINT i = 0; i < (UINT)LEVEL_TYPE::END; ++i)
	{
		m_arrLevels[i]->init();
	}


	// Level 
	ChangeLevel(LEVEL_TYPE::TITLE_LEVEL);
}

void CLevelMgr::tick()
{
	if (nullptr == m_pCurLevel)
		return;

	m_pCurLevel->tick();
}

void CLevelMgr::render(HDC _dc)
{
	if (nullptr == m_pCurLevel)
		return;

	// Level render
	m_pCurLevel->render(_dc);
}
