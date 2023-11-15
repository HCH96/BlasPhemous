#include "pch.h"
#include "CCandle.h"

#include "CAssetMgr.h"
#include "CTexture.h"

CCandle::CCandle(int _Idx)
{
	SetScale(Vec2(2.f, 2.f));

	m_pAnimator = AddComponent<CAnimator>(L"Candle");

	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"candlegroup02", L"texture\\Object\\MetaObject\\candlegroup02.png");
	m_pAnimator->LoadAnimation(pTex, L"candlegroup02", L"animdata\\Object\\candlegroup02.txt");
	m_pAnimator->SetAnimDuration(L"candlegroup02", 0.1f);

	pTex = CAssetMgr::GetInst()->LoadTexture(L"candlegroup04", L"texture\\Object\\MetaObject\\candlegroup04.png");
	m_pAnimator->LoadAnimation(pTex, L"candlegroup04", L"animdata\\Object\\candlegroup04.txt");
	m_pAnimator->SetAnimDuration(L"candlegroup04", 0.1f);

	if (_Idx == 2)
	{
		m_pAnimator->Play(L"candlegroup02",true);
	}
	else
	{
		m_pAnimator->Play(L"candlegroup04",true);
	}


}

CCandle::CCandle(const CCandle& _Origin)
{
}

CCandle::~CCandle()
{
}
