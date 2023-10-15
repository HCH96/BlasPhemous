#include "pch.h"
#include "CBtnUI.h"

CBtnUI::CBtnUI()
{
}

CBtnUI::~CBtnUI()
{
}

void CBtnUI::tick(float _DT)
{
	// 본인 tick


	// component tick -> ChildUI tick
	Super::tick(_DT);
}

void CBtnUI::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	Rectangle(_dc, (int)vPos.x, (int)vPos.y, int(vPos.x + vScale.x), int(vPos.y + vScale.y));

	// 부모클래스(CUI) 렌더함수 호출(자식 UI 들한테 render 를 호출한다)
	// Component render -> ChildUI render
	Super::render(_dc);

}

