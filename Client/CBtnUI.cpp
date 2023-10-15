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
	// ���� tick


	// component tick -> ChildUI tick
	Super::tick(_DT);
}

void CBtnUI::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	Rectangle(_dc, (int)vPos.x, (int)vPos.y, int(vPos.x + vScale.x), int(vPos.y + vScale.y));

	// �θ�Ŭ����(CUI) �����Լ� ȣ��(�ڽ� UI ������ render �� ȣ���Ѵ�)
	// Component render -> ChildUI render
	Super::render(_dc);

}

