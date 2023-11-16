#include "pch.h"
#include "CBackground.h"

#include "CEngine.h"
#include "CCamera.h"

#include "CTexture.h"

CBackground::CBackground()
	: m_pTex(nullptr)
	, m_vParallaxSpeed{1.f,1.f}
{
}

CBackground::~CBackground()
{
}


void CBackground::tick(float _DT)
{
}

void CBackground::render(HDC _dc)
{
	if (m_pTex == nullptr)
		return;


	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	
	// Offset
	Vec2 vPos = GetPos();
	
	// 확대 배율
	Vec2 vScale = GetScale();

	// CurLookAt
	Vec2 vCurLookAt = CCamera::GetInst()->GetCurLookAt();
	
	// Texture LeftTop
	Vec2 vCurTexLeftTop = (CCamera::GetInst()->GetCurLookAt() - vResolution /2.f) / vScale;
	vCurTexLeftTop *= m_vParallaxSpeed;
	
	// Texture Render Size
	Vec2 vTextureRenderSize = vResolution / vScale;

	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;

	blend.SourceConstantAlpha = 255; // 0 ~ 255
	blend.AlphaFormat = AC_SRC_ALPHA; // 0

	AlphaBlend(_dc
		, 0, 0
		, (int)vResolution.x, (int)vResolution.y
		, m_pTex->GetDC()
		, (int)vCurTexLeftTop.x - int(vPos.x / vScale.x)
		, (int)vCurTexLeftTop.y - int(vPos.y / vScale.y)
		, (int)vTextureRenderSize.x, (int)vTextureRenderSize.y
		, blend);

}

