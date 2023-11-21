#include "pch.h"
#include "CLightning.h"

#include "CAssetMgr.h"
#include "CTexture.h"

CLightning::CLightning()
	: m_pAnimator(nullptr)
	, m_pCollider(nullptr)
	, m_bIsOn(false)
	, m_iPrevFrame(0)
{
	SetScale(Vec2(2.f, 2.f));

	m_pAnimator = AddComponent<CAnimator>(L"Lightning");

	// Spawn
	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"lightningBolt_Tileable_fxs", L"texture\\Effect\\lightningBolt_Tileable_fxs.png");

	m_pAnimator->LoadAnimation(pTex, L"On", L"animdata\\Effect\\lightningBolt_Tileable_fxs.txt");

	m_pAnimator->SetAnimDuration(L"On", 0.04f);


	// Collider
	m_pCollider = AddComponent<CCollider>(L"Lightning");
	m_pCollider->SetScale(Vec2(50.f, 800.f));
	m_pCollider->SetOffsetPos(Vec2(0.f, -400.f));
	m_pCollider->SetTime(0.5f);



}

CLightning::~CLightning()
{
}


void CLightning::On(Vec2 _vPos)
{
	SetPos(_vPos);

	m_bIsOn = true;
	m_iPrevFrame = 0;

	m_pAnimator->Play(L"On", true);

	m_pCollider->SetTime(0.f);

	//m_pCollider->SetTime(10.f);
	//m_pCollider->On();

	
}

void CLightning::Off()
{
	// Collider Off
	m_pAnimator->Stop();
	m_pCollider->SetTime(0.f);
	m_bIsOn = false;


}

void CLightning::tick(float _DT)
{
	if (!m_bIsOn)
		return;

	Super::tick(_DT);

	int iCurFrame = m_pAnimator->GetCurFrame();

	// On 상태일 때
	if (m_bIsOn)
	{
		if (m_iPrevFrame == 51 && iCurFrame == 52)
		{
			m_pCollider->SetTime(0.2f);
			m_pCollider->On();
		}

		if (m_pAnimator->IsFinish())
		{
			Off();
		}

	}

	m_iPrevFrame = iCurFrame;

}

void CLightning::render(HDC _dc)
{
	Super::render(_dc);
}


