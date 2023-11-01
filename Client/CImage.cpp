#include "pch.h"
#include "CImage.h"

#include "CTexture.h"
#include "CKeyMgr.h"

CImage::CImage()
	: m_pTex(nullptr)
	, m_pAnimator(nullptr)
{
	m_pAnimator = AddComponent<CAnimator>(L"");
}

CImage::~CImage()
{
}



void CImage::SetScaleToTex()
{
	Vec2 vScale = Vec2(m_pTex->GetWidth(), m_pTex->GetHeight());
	SetScale(vScale);
}

void CImage::tick(float _DT)
{
	Super::tick(_DT);
}

void CImage::render(HDC _dc)
{
	if (m_pTex == nullptr)
	{
		Super::render(_dc);
		return;
	}

	Vec2 vRenderPos = GetRenderPos();
	Vec2 vScale = GetScale();

	AlphaBlendRender(_dc, m_pTex, vRenderPos, vScale);
}
