#include "pch.h"
#include "CPenitentUI.h"

#include "CAssetMgr.h"

#include "CTexture.h"

#include "CPenitentHP.h"
#include "CPenitentMP.h"
#include "CPenitentPotion.h"

CPenitentUI::CPenitentUI()
{
	m_pTexture = CAssetMgr::GetInst()->LoadTexture(L"PenitentUI", L"texture\\UI\\Player_HpBar.png");
	SetPos(Vec2(20.f, 20.f));
	SetScale(Vec2(m_pTexture->GetWidth(), m_pTexture->GetHeight()));

	CPenitentHP* pHPBar = new CPenitentHP;
	AddChildUI(pHPBar);

	CPenitentMP* pMPBar = new CPenitentMP;
	AddChildUI(pMPBar);

	CPenitentPotion* pPotion = new CPenitentPotion;
	AddChildUI(pPotion);


}

CPenitentUI::~CPenitentUI()
{
}


void CPenitentUI::tick(float _DT)
{
	Super::tick(_DT);
}

void CPenitentUI::render(HDC _dc)
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

