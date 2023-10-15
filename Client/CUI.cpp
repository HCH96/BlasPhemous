#include "pch.h"
#include "CUI.h"

CUI::CUI()
{
}

CUI::~CUI()
{
}


void CUI::tick(float _DT)
{
	Super::tick(_DT);

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

