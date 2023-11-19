#include "pch.h"
#include "CBossPanel.h"

#include "CAssetMgr.h"
#include "CTexture.h"

#include "CBossHP.h"

CBossPanel::CBossPanel()
	: m_pTexture(nullptr)
{
	m_pTexture = CAssetMgr::GetInst()->LoadTexture(L"BossPanel", L"texture\\UI\\Boss_HpBarFrame.png");
	SetPos(Vec2(294.f, 650.f));
	SetScale(Vec2(m_pTexture->GetWidth(), m_pTexture->GetHeight()));

	CBossHP* pHP = new CBossHP;
	AddChildUI(pHP);
}

CBossPanel::~CBossPanel()
{
}

void CBossPanel::begin()
{
	Super::begin();

}

void CBossPanel::tick(float _DT)
{
	Super::tick(_DT);
}

void CBossPanel::render(HDC _dc)
{
	Super::render(_dc);

	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;

	blend.SourceConstantAlpha = 255; // 0 ~ 255
	blend.AlphaFormat = AC_SRC_ALPHA; // 0

	AlphaBlend(_dc
		, (int)vPos.x, (int)vPos.y
		, int(vScale.x), int(vScale.y)
		, m_pTexture->GetDC()
		, 0, 0
		, int(vScale.x), int(vScale.y)
		, blend);

}
