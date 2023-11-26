#include "pch.h"
#include "CBossPanel.h"

#include "CAssetMgr.h"
#include "CTexture.h"

#include "CBossHP.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CObj.h"

#include "CPope.h"
#include "Pontiff.h"
#include "CElderBrother.h"

CBossPanel::CBossPanel()
	: m_pTexture(nullptr)
	, m_bOn(false)
{
	SetName(L"BossPanel");

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
	if (m_bOn == false)
	{
		return;
	}


	UINT iCurLv = CLevelMgr::GetInst()->GetCurLeveli();
	CLevel* pCurLv = CLevelMgr::GetInst()->GetCurLevel();


	if (iCurLv == (UINT)LEVEL_TYPE::STAGE01_4)
	{
		CObj* pBoss = pCurLv->GetBoss();
		CElderBrother* pElder = dynamic_cast<CElderBrother*>(pBoss);

		if (pElder->GetHP() <= 0.f)
		{
			return;
		}
	}
	else if (iCurLv == (UINT)LEVEL_TYPE::STAGE02_2)
	{
		CObj* pBoss = pCurLv->GetBoss();
		CPope* pPope = dynamic_cast<CPope*>(pBoss);

		if (pPope->GetHP() <= 0.f)
		{
			return;
		}
	}
	else if (iCurLv == (UINT)LEVEL_TYPE::STAGE02_3)
	{
		CObj* pBoss = pCurLv->GetBoss();
		Pontiff* pPontiff = dynamic_cast<Pontiff*>(pBoss);

		if (pPontiff->GetHP() <= 0.f)
		{
			return;
		}
	}

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

	if (m_pName == nullptr)
		return;

	int ixStart = vPos.x + vScale.x / 2.f - m_pName->GetWidth()/2.f;

	AlphaBlend(_dc
		, ixStart, (int)vPos.y - 30
		, m_pName->GetWidth(), m_pName->GetHeight()
		, m_pName->GetDC()
		, 0, 0
		, m_pName->GetWidth(), m_pName->GetHeight()
		, blend);

}
