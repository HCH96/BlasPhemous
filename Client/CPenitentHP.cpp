#include "pch.h"
#include "CPenitentHP.h"

#include "CAssetMgr.h"
#include "CLevelMgr.h"

#include "CTexture.h"

#include "CPenitent.h"


CPenitentHP::CPenitentHP()
	: m_pTexture(nullptr)
	, m_fCurHP(100.f)
	, m_fPrevHP(100.f)
	, m_fDecreasingSpeed(0.f)
{
	m_pTexture = CAssetMgr::GetInst()->LoadTexture(L"Player_HP", L"texture\\UI\\Player_HP.png");
	SetPos(Vec2(100.f, 20.f));
	SetScale(Vec2(m_pTexture->GetWidth(), m_pTexture->GetHeight()));
}

CPenitentHP::~CPenitentHP()
{
}

void CPenitentHP::tick(float _DT)
{
	Super::tick(_DT);

	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();

	m_fCurHP = pPenitent->GetHP();
	
	if (m_fCurHP < m_fPrevHP)
	{
		m_fDecreasingSpeed = (m_fPrevHP - m_fCurHP) / 0.3f;
		if (m_fDecreasingSpeed < 20.f)
		{
			m_fDecreasingSpeed = 20.f;
		}

		m_fPrevHP -= m_fDecreasingSpeed * _DT;
	}

	if (m_fCurHP > m_fPrevHP)
	{
		m_fPrevHP = m_fCurHP;
	}

}

void CPenitentHP::render(HDC _dc)
{
	Super::render(_dc);

	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();
	float fRatio = m_fPrevHP / 100.f;
	float fRenderSize = vScale.x * fRatio;

	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;

	blend.SourceConstantAlpha = 255; // 0 ~ 255
	blend.AlphaFormat = AC_SRC_ALPHA; // 0

	AlphaBlend(_dc
		, (int)vPos.x, (int)vPos.y
		, (int)fRenderSize, int(vScale.y)
		, m_pTexture->GetDC()
		, 0, 0
		, int(vScale.x), int(vScale.y)
		, blend);
}


