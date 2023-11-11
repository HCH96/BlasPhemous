#include "pch.h"
#include "CPenitentMP.h"

#include "CLevelMgr.h"
#include "CAssetMgr.h"

#include "CTexture.h"

#include "CPenitent.h"

CPenitentMP::CPenitentMP()
	: m_pTexture(nullptr)
	, m_fCurMP(100.f)
	, m_fPrevMP(100.f)
	, m_fDecreasingSpeed(0.f)
{
	m_pTexture = CAssetMgr::GetInst()->LoadTexture(L"Player_MP", L"texture\\UI\\Player_MP.png");
	SetPos(Vec2(158.f, 45.f));
	SetScale(Vec2(m_pTexture->GetWidth(), m_pTexture->GetHeight()));

	// MP ÁÂÇ¥°ª ³Ö±â
	m_vecMPIdx.push_back(0.f);
	m_vecMPIdx.push_back(31.f);
	m_vecMPIdx.push_back(68.f);
	m_vecMPIdx.push_back(100.f);
}

CPenitentMP::~CPenitentMP()
{
}


void CPenitentMP::tick(float _DT)
{
	Super::tick(_DT);

	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();

	m_fCurMP = m_vecMPIdx[pPenitent->GetMP()];



	if (m_fCurMP < m_fPrevMP)
	{
		m_fDecreasingSpeed = (m_fPrevMP - m_fCurMP) / 0.3f;
		if (m_fDecreasingSpeed < 20.f)
		{
			m_fDecreasingSpeed = 20.f;
		}

		m_fPrevMP -= m_fDecreasingSpeed * _DT;
	}

	if (m_fCurMP > m_fPrevMP)
	{
		m_fPrevMP = m_fCurMP;
	}
}

void CPenitentMP::render(HDC _dc)
{
	Super::render(_dc);

	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();
	float fRatio = m_fPrevMP / 100.f;
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

