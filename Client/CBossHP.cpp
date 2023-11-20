#include "pch.h"
#include "CBossHP.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CElderBrother.h"

#include "CAssetMgr.h"
#include "CTexture.h"

#include "CElderBrother.h"
#include "CPope.h"



CBossHP::CBossHP()
	: m_pHP(nullptr)
	, m_pHPBack(nullptr)
	, m_pBoss(nullptr)
	, m_fCurHP(100.f)
	, m_fPrevHP(100.f)
	, m_fDecreasingSpeed(0.f)
	, m_fMaxHP(100.f)
{
	m_pHP = CAssetMgr::GetInst()->LoadTexture(L"BossHPBar", L"texture\\UI\\BossHPBar.png");
	m_pHPBack = CAssetMgr::GetInst()->LoadTexture(L"BossHPBarBack", L"texture\\UI\\BossHPBar_Back.png");
	SetPos(Vec2(57.f, 24.f));
	SetScale(Vec2(m_pHP->GetWidth(), m_pHP->GetHeight()));

}

CBossHP::~CBossHP()
{
}

void CBossHP::begin()
{
	// 보스 가져오기
	m_pBoss = CLevelMgr::GetInst()->GetCurLevel()->GetBoss();

	UINT iCurLv = CLevelMgr::GetInst()->GetCurLeveli();

	if (iCurLv == (UINT)LEVEL_TYPE::STAGE01_4)
	{
		m_fMaxHP = 12.f;
		m_fCurHP = 12.f;
		m_fPrevHP = 12.f;
	}
	else if (iCurLv == (UINT)LEVEL_TYPE::STAGE02_2)
	{
		m_fMaxHP = 10.f;
		m_fCurHP = 10.f;
		m_fPrevHP = 10.f;
	}
	

}

void CBossHP::tick(float _DT)
{
	Super::tick(_DT);


	UINT iCurLv = CLevelMgr::GetInst()->GetCurLeveli();
	CLevel* pCurLv = CLevelMgr::GetInst()->GetCurLevel();


	if (iCurLv == (UINT)LEVEL_TYPE::STAGE01_4)
	{
		CObj* pBoss = pCurLv->GetBoss();
		CElderBrother* pElder = dynamic_cast<CElderBrother*>(pBoss);

		m_fCurHP = pElder->GetHP();
	}
	else if (iCurLv == (UINT)LEVEL_TYPE::STAGE02_2)
	{
		CObj* pBoss = pCurLv->GetBoss();
		CPope* pElder = dynamic_cast<CPope*>(pBoss);

		m_fCurHP = pElder->GetHP();
	}


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

void CBossHP::render(HDC _dc)
{
	Super::render(_dc);

	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();


	// HPBack
	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;

	blend.SourceConstantAlpha = 255; // 0 ~ 255
	blend.AlphaFormat = AC_SRC_ALPHA; // 0

	AlphaBlend(_dc
		, (int)vPos.x, (int)vPos.y
		, (int)vScale.x, int(vScale.y)
		, m_pHPBack->GetDC()
		, 0, 0
		, int(vScale.x), int(vScale.y)
		, blend);


	//HP
	float fHPRatio = m_fPrevHP / m_fMaxHP;
	float fHPRenderSize = vScale.x * fHPRatio;


	AlphaBlend(_dc
		, (int)vPos.x, (int)vPos.y
		, (int)fHPRenderSize, int(vScale.y)
		, m_pHP->GetDC()
		, 0, 0
		, int(fHPRenderSize), int(vScale.y)
		, blend);

}

