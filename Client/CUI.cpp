#include "pch.h"
#include "CUI.h"

#include "CKeyMgr.h"

CUI::CUI()
	: m_pParentUI(nullptr)
	, m_vFinalPos{}
{
}

CUI::CUI(const CUI& _Origin)
	: CObj(_Origin)
	, m_pParentUI(nullptr)
{
	for (size_t i = 0; i < _Origin.m_vecChildUI.size(); ++i)
	{
		AddChildUI(_Origin.m_vecChildUI[i]->Clone());
	}

}

CUI::~CUI()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		if (nullptr != m_vecChildUI[i])
			delete m_vecChildUI[i];
	}
}


void CUI::tick(float _DT)
{
	Super::tick(_DT);

	// 최종 좌표 연산
	m_vFinalPos = GetPos();

	if (nullptr != m_pParentUI)
	{
		m_vFinalPos += m_pParentUI->GetPos();
	}

	// 자식 UI tick()
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->tick(_DT);
	}
}

void CUI::render(HDC _dc)
{
	// Component render
	Super::render(_dc);

	// Child render
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->render(_dc);
	}
}

