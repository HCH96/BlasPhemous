#include "pch.h"
#include "CTearsUI.h"

#include "CLevelMgr.h"

#include "CPenitent.h"

#include "CAssetMgr.h"

#include "CTexture.h"

CTearsUI::CTearsUI()
	: m_pTexture(nullptr)
	, m_fCur(0.f)
	, m_fRender(0.f)
{
	m_pTexture = CAssetMgr::GetInst()->LoadTexture(L"TearFrame", L"texture\\UI\\TearFrame.png");
	SetPos(Vec2(1080.f, -20.f));
	SetScale(Vec2(m_pTexture->GetWidth(), m_pTexture->GetHeight()));

	m_vNumPos = Vec2(1175.f, 65.f);

	// Number Tex Init
	m_vecTex.resize(10);

	m_vecTex[0] = CAssetMgr::GetInst()->LoadTexture(L"Num_0", L"texture\\UI\\0.png");
	m_vecTex[1] = CAssetMgr::GetInst()->LoadTexture(L"Num_1", L"texture\\UI\\1.png");
	m_vecTex[2] = CAssetMgr::GetInst()->LoadTexture(L"Num_2", L"texture\\UI\\2.png");
	m_vecTex[3] = CAssetMgr::GetInst()->LoadTexture(L"Num_3", L"texture\\UI\\3.png");
	m_vecTex[4] = CAssetMgr::GetInst()->LoadTexture(L"Num_4", L"texture\\UI\\4.png");
	m_vecTex[5] = CAssetMgr::GetInst()->LoadTexture(L"Num_5", L"texture\\UI\\5.png");
	m_vecTex[6] = CAssetMgr::GetInst()->LoadTexture(L"Num_6", L"texture\\UI\\6.png");
	m_vecTex[7] = CAssetMgr::GetInst()->LoadTexture(L"Num_7", L"texture\\UI\\7.png");
	m_vecTex[8] = CAssetMgr::GetInst()->LoadTexture(L"Num_8", L"texture\\UI\\8.png");
	m_vecTex[9] = CAssetMgr::GetInst()->LoadTexture(L"Num_9", L"texture\\UI\\9.png");
}

CTearsUI::~CTearsUI()
{
}


void CTearsUI::tick(float _DT)
{
	Super::tick(_DT);

	CPenitent* pPenitent = CLevelMgr::GetInst()->GetPenitent();
	m_fCur = pPenitent->GetTears();

	// 작아져야 할 때
	if (m_fCur < m_fRender)
	{
		m_fRender -= 100.f * _DT;

		if (m_fRender < m_fCur)
		{
			m_fRender = m_fCur;
		}
	}
	// 커져야 할 때
	else if (m_fCur > m_fRender)
	{
		m_fRender += 100.f * _DT;

		if (m_fRender > m_fCur)
		{
			m_fRender = m_fCur;
		}
	}
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


	int iRenderTear = (int)m_fRender;
	Vec2 vNumRenderPos = m_vNumPos;

	AlphaBlend(_dc
		, (int)vPos.x, (int)vPos.y
		, int(vScale.x * 2.f), int(vScale.y * 2.f)
		, m_pTexture->GetDC()
		, 0, 0
		, int(vScale.x), int(vScale.y)
		, blend);

	while (iRenderTear >= 0)
	{
		int iRenderTex = iRenderTear % 10;
		Vec2 vNumScale = Vec2(m_vecTex[iRenderTex]->GetWidth(), m_vecTex[iRenderTex]->GetHeight());

		AlphaBlend(_dc
			, int(vNumRenderPos.x-vNumScale.x/2.f)
			, int(vNumRenderPos.y-vNumScale.y/2.f)
			, int(vNumScale.x), int(vNumScale.y)
			, m_vecTex[iRenderTex]->GetDC()
			, 0, 0
			, int(vNumScale.x), int(vNumScale.y)
			, blend);

		vNumRenderPos.x -= vNumScale.x + 5.f;

		iRenderTear = iRenderTear / 10;

		if (iRenderTear == 0)
			break;
	}


	
}

