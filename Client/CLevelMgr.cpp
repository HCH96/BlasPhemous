#include "pch.h"
#include "CLevelMgr.h"

#include "CStartLevel.h"
#include "CEditorLevel.h"
#include "CPlayLevel.h"

CLevelMgr::CLevelMgr()
	: m_pCurLevel(nullptr)
	, m_arrLevels{}
{}


CLevelMgr::~CLevelMgr()
{
	for (UINT i = 0; i < (UINT)LEVEL_TYPE::END; ++i)
	{
		if (nullptr != m_arrLevels[i])
		{
			delete m_arrLevels[i];
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
	// 모든 레벨 생성
	m_arrLevels[(UINT)LEVEL_TYPE::START_LEVEL] = new CStartLevel;
	m_arrLevels[(UINT)LEVEL_TYPE::PLAY_LEVEL] = new CPlayLevel;
	m_arrLevels[(UINT)LEVEL_TYPE::EDITOR_LEVEL] = new CEditorLevel;

	// 레벨 초기화
	for (UINT i = 0; i < (UINT)LEVEL_TYPE::END; ++i)
	{
		m_arrLevels[i]->init();
	}

	// Level 
	ChangeLevel(LEVEL_TYPE::PLAY_LEVEL);

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
