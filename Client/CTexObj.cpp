#include "pch.h"
#include "CTexObj.h"

#include "CTexture.h"

CTexObj::CTexObj()
	: m_pTex(nullptr)
{
}

CTexObj::~CTexObj()
{
}

void CTexObj::render(HDC _dc)
{
	Vec2 vRenderPos = GetRenderPos();
	Vec2 vScale = GetScale();
	Vec2 vSize = Vec2(m_pTex->GetWidth(), m_pTex->GetHeight());


	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;

	blend.SourceConstantAlpha = 255; // 0 ~ 255
	blend.AlphaFormat = AC_SRC_ALPHA; // 0

	AlphaBlend(_dc
		, int(vRenderPos.x - vSize.x / 2.f)
		, int(vRenderPos.y - vSize.y)
		, int(vSize.x * GetScale().x)
		, int(vSize.y * GetScale().y)
		, m_pTex->GetDC()
		, 0, 0
		, int(vSize.x)
		, int(vSize.y)
		, blend);



}