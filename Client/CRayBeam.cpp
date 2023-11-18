#include "pch.h"
#include "CRayBeam.h"

#include "CAssetMgr.h"
#include "CTexture.h"

#include "CPenitent.h"

CRayBeam::CRayBeam()
	: m_pSpawner(nullptr)
	, m_pAnimator(nullptr)
	, m_pCollider(nullptr)
	, m_bIsOn(false)
	, m_bDir(true)
{
	m_pAnimator = AddComponent<CAnimator>();

	// On
	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"RayBeam", L"texture\\Object\\MetaObject\\burntFace_rayBeam_impact.png");
	CTexture* pTexReverse = CAssetMgr::GetInst()->LoadTextureReverse(L"RayBeam_L", L"texture\\Object\\MetaObject\\burntFace_rayBeam_impact.png");

	m_pAnimator->LoadAnimation(pTex, L"Impact", L"animdata\\Object\\burntFace_rayBeam_impact.txt");
	m_pAnimator->LoadAnimation(pTexReverse, L"Impact_L", L"animdata\\Object\\burntFace_rayBeam_impact.txt", true);

	m_pAnimator->SetAnimDuration(L"Impact", 0.06f);
	m_pAnimator->SetAnimDuration(L"Impact_L", 0.06f);

	// Collider
	m_pCollider = AddComponent<CCollider>(L"RayBeam");
	m_pCollider->SetScale(Vec2(50.f, 50.f));
	m_pCollider->SetOffsetPos(Vec2(0.f, -25.f));
	m_pCollider->SetTime(0.5f);

}

CRayBeam::~CRayBeam()
{
}

void CRayBeam::On(Vec2 _vPos, bool _bDir)
{
	SetPos(_vPos);


	m_bIsOn = true;
	m_bDir = _bDir;

	if (m_bDir)
	{
		m_pAnimator->Play(L"Impact", false);
	}
	else
	{
		m_pAnimator->Play(L"Impact_L", false);
	}

	m_pCollider->SetTime(0.5f);
	m_pCollider->On();

}

void CRayBeam::Off()
{
	// Collider Off
	m_pAnimator->Stop();
	m_pCollider->SetTime(0.f);
	m_bIsOn = false;
}

void CRayBeam::tick(float _DT)
{
	if (!m_bIsOn)
		return;

	Super::tick(_DT);

	// On 상태일 때
	if (m_bIsOn)
	{
		if (m_pAnimator->IsFinish())
		{
			Off();
		}
	}
	// Off 상태일 때

}

void CRayBeam::render(HDC _dc)
{

	Super::render(_dc);
}

void CRayBeam::BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol)
{
	if (_pOtherCol->GetName() != L"Penitent_Collider")
		return;
}

