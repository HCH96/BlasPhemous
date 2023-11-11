#include "pch.h"
#include "CPenitentPotion.h"

#include "CLevelMgr.h"

#include "CAssetMgr.h"

#include "CTexture.h"

#include "CPenitent.h"

CPenitentPotion::CPenitentPotion()
	: m_iCount(3)
	, m_iCur(3)
	, m_iInterval(40)

{
	m_pFullPotion = CAssetMgr::GetInst()->LoadTexture(L"Full_Flask", L"texture\\UI\\Full_Flask.png");
	m_pEmptyPotion = CAssetMgr::GetInst()->LoadTexture(L"Empty_Flask", L"texture\\UI\\Empty_Flask.png");

	SetPos(Vec2(120.f, 80.f));
	SetScale(Vec2(m_pFullPotion->GetWidth(), m_pFullPotion->GetHeight()));
}

CPenitentPotion::~CPenitentPotion()
{
}

void CPenitentPotion::tick(float _DT)
{
	Super::tick(_DT);

	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();

	m_iCur = pPenitent->GetPotionCount();

}

void CPenitentPotion::render(HDC _dc)
{
	Super::render(_dc);

	CTexture* pRenderTex = nullptr;


	for (int i = 0; i < m_iCount; ++i)
	{
		Vec2 vPos = GetFinalPos();
		Vec2 vScale = GetScale();

		BLENDFUNCTION blend = {};
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;

		blend.SourceConstantAlpha = 255; // 0 ~ 255
		blend.AlphaFormat = AC_SRC_ALPHA; // 0

		if (i < m_iCur)
		{
			pRenderTex = m_pFullPotion;
		}
		else
		{
			pRenderTex = m_pEmptyPotion;
		}


		AlphaBlend(_dc
			, (int)vPos.x + m_iInterval * i, (int)vPos.y
			, int(vScale.x), int(vScale.y)
			, pRenderTex->GetDC()
			, 0, 0
			, int(vScale.x), int(vScale.y)
			, blend);

	}

}

