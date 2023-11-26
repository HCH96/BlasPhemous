#include "pch.h"
#include "CAshCloud.h"

#include "CAssetMgr.h"
#include "CTexture.h"

CAshCloud::CAshCloud()
	:m_pTex(nullptr)
	, m_fAcc(0.f)
{
	SetScale(Vec2(2.f, 2.f));
}

CAshCloud::~CAshCloud()
{
}

void CAshCloud::tick(float _DT)
{
	Super::tick(_DT);

	m_fAcc += _DT;

	Vec2 vPos = GetPos();

	if (GetDir())
	{
		vPos.x += 1000.f * _DT;
	}
	else
	{
		vPos.x -= 1000.f * _DT;
	}

	SetPos(vPos);


	if (m_fAcc > 5.f)
	{
		Destroy();
	}
}

void CAshCloud::render(HDC _dc)
{
	Super::render(_dc);

	Vec2 vRenderPos = GetRenderPos();
	Vec2 vScale = GetScale();
	Vec2 vSize = Vec2(m_pTex->GetWidth(), m_pTex->GetHeight());


	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;

	blend.SourceConstantAlpha = 255; // 0 ~ 255
	blend.AlphaFormat = AC_SRC_ALPHA; // 0

	AlphaBlend(_dc
		, int(vRenderPos.x - (vSize.x / 2.f) * vScale.x )
		, int(vRenderPos.y - (vSize.y * vScale.y))
		, int(vSize.x * GetScale().x)
		, int(vSize.y * GetScale().y)
		, m_pTex->GetDC()
		, 0, 0
		, m_pTex->GetWidth()
		, m_pTex->GetHeight()
		, blend);




}
