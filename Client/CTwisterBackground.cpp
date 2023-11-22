#include "pch.h"
#include "CTwisterBackground.h"

#include "CTexture.h"

CTwisterBackground::CTwisterBackground()
	: m_pTex(nullptr)
	, m_bAlphaUP(true)
	, m_fSpeed(200.f)
{
}

CTwisterBackground::~CTwisterBackground()
{
}



void CTwisterBackground::tick(float _DT)
{
	Super::tick(_DT);

	Vec2 vPos = GetPos();

	vPos.x += m_fSpeed * _DT;
	if (vPos.x + 160.f > 640.f)
	{
		vPos.x = 480.f;
		m_fSpeed *= -1;
	}
	else if (vPos.x <0.f)
	{
		vPos.x = 0.f;
		m_fSpeed *= -1;
	}

	SetPos(vPos);



	if (m_bAlphaUP)
	{
		m_fAlpha += 30.f * _DT;

		if (m_fAlpha > m_fMaxAlpha)
		{
			m_fAlpha = m_fMaxAlpha;
			m_bAlphaUP = false;
		}

	}
	else
	{
		m_fAlpha -= 30.f * _DT;

		if (m_fAlpha < m_fMinAlpha)
		{
			m_fAlpha = m_fMinAlpha;
			m_bAlphaUP = true;
		}
	}


}

void CTwisterBackground::render(HDC _dc)
{
	Vec2 vPos = GetPos();


	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;

	blend.SourceConstantAlpha = (int)m_fAlpha; // 0 ~ 255
	blend.AlphaFormat = AC_SRC_ALPHA; // 0

	AlphaBlend(_dc 
		, 0 , 0
		, 1280, 720
		, m_pTex->GetDC()
		, (int)vPos.x, 0
		, 160, 640
		, blend);




	Super::render(_dc);
}

