#include "pch.h"
#include "CTearsUI.h"

#include "CAssetMgr.h"

#include "CTexture.h"

CTearsUI::CTearsUI()
	: m_pTexture(nullptr)
{
	m_pTexture = CAssetMgr::GetInst()->LoadTexture(L"TearFrame", L"texture\\UI\\TearFrame.png");
	SetPos(Vec2(1080.f, -20.f));
	SetScale(Vec2(m_pTexture->GetWidth(), m_pTexture->GetHeight()));
}

CTearsUI::~CTearsUI()
{
}


void CTearsUI::tick(float _DT)
{
	Super::tick(_DT);
}

void CTearsUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;

	blend.SourceConstantAlpha = 255; // 0 ~ 255
	blend.AlphaFormat = AC_SRC_ALPHA; // 0

	AlphaBlend(_dc
		, (int)vPos.x, (int)vPos.y
		, int(vScale.x * 2.f), int(vScale.y * 2.f)
		, m_pTexture->GetDC()
		, 0, 0
		, int(vScale.x), int(vScale.y)
		, blend);
}

