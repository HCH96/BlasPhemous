#include "pch.h"
#include "CPanelUI.h"



#include "CKeyMgr.h"

CPanelUI::CPanelUI()
{
	
}

CPanelUI::~CPanelUI()
{
}


void CPanelUI::tick(float _DT)
{
	Super::tick(_DT);
}

void CPanelUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();
	Rectangle(_dc, (int)vPos.x, (int)vPos.y, int(vPos.x + vScale.x), int(vPos.y + vScale.y));

	Super::render(_dc);
}
