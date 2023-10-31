#include "pch.h"
#include "CMonster.h"

#include "components.h"

#include "CAssetMgr.h"
#include "CTexture.h"

#include "CProjectile.h"

#include "CNormalMonIdle.h"
#include "CNormalMonTrace.h"


CMonster::CMonster()
	: m_Info{}
	, m_pCollider(nullptr)
	, m_pTexture(nullptr)
	, m_pAI(nullptr)
{
	m_pCollider = AddComponent<CCollider>(L"MonsterCollider");
	m_Info.HP = 5;
	m_pTexture = CAssetMgr::GetInst()->LoadTexture(L"StartTex", L"texture\\MagicCircle_01.png");

	// 상태머신 컴포넌트 추가 및 설정
	m_pAI = AddComponent<CStateMachine>(L"AI");
	m_pAI->AddState((UINT)ENORMAL_MON_STATE::NORMAL_MON_IDLE, new CNormalMonIdle);
	m_pAI->AddState((UINT)ENORMAL_MON_STATE::NORMAL_MON_TRACE, new CNormalMonTrace);
}

CMonster::CMonster(const CMonster& _Origin)
	: CObj(_Origin)
	, m_Info(_Origin.m_Info)
	, m_pCollider(nullptr)
	, m_pTexture(_Origin.m_pTexture)
	, m_pAI(nullptr)
{
	m_pCollider = GetComponent<CCollider>();
	m_pAI = GetComponent<CStateMachine>();
}

CMonster::~CMonster()
{
}

void CMonster::begin()
{
	m_pCollider->SetScale(GetScale() - 10.f);

	Vec2 vPos = GetPos();
	m_pAI->AddDataToBlackboard(L"Initial Position", vPos);
	m_pAI->AddDataToBlackboard(L"Detect Range", 500.f);
	m_pAI->AddDataToBlackboard(L"Attack Range", 50.f);
	m_pAI->AddDataToBlackboard(L"Speed", 100.f);


	m_pAI->ChangeState((UINT)ENORMAL_MON_STATE::NORMAL_MON_IDLE);
}

void CMonster::tick(float _DT)
{
	Super::tick(_DT);
}

void CMonster::render(HDC _dc)
{
	Vec2 vRenderPos = GetRenderPos();
	Vec2 vScale = GetScale();

	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;

	blend.SourceConstantAlpha = 255; // 0 ~ 255
	blend.AlphaFormat = AC_SRC_ALPHA; // 0

	AlphaBlend(_dc
		, int(vRenderPos.x - m_pTexture->GetWidth() / 2.f)
		, int(vRenderPos.y - m_pTexture->GetHeight() / 2.f)
		, m_pTexture->GetWidth()
		, m_pTexture->GetHeight()
		, m_pTexture->GetDC()
		, 0, 0
		, m_pTexture->GetWidth()
		, m_pTexture->GetHeight()
		, blend);

	Super::render(_dc);
}


void CMonster::BeginOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol)
{
	if (dynamic_cast<CProjectile*>(_pOtherObj))
	{
		m_Info.HP -= 1.f;

		if (m_Info.HP <= 0.f)
		{
			Destroy();
		}
	}

}