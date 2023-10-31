#include "pch.h"
#include "CCollider.h"

#include "CObj.h"
#include "CCamera.h"
#include "CEngine.h"

#include "CLevel.h"
#include "CLevelMgr.h"
#include "CLayer.h"

CCollider::CCollider(CObj* _pOwner)
	: CComponent(_pOwner)
	, m_iCollisionCount(0)
{
}

CCollider::CCollider(const CCollider& _Origin)
	: CComponent(_Origin)
	, m_vOffsetPos(_Origin.m_vOffsetPos)
	, m_vScale(_Origin.m_vScale)
	, m_vFinalPos(_Origin.m_vFinalPos)
	, m_iCollisionCount(0)
{
}

CCollider::~CCollider()
{
}

void CCollider::finaltick(float _DT)
{
	Vec2 vOwnerPos = GetOwner()->GetPos();

	m_vFinalPos = vOwnerPos + m_vOffsetPos;

	// 현재 속해있는 레이어에 충돌체(본인) 를 등록

	int iLayerIdx = GetOwner()->GetLayerIdx();
	assert(!(iLayerIdx < 0));

	CLayer* pCurLayer = CLevelMgr::GetInst()->GetCurLevel()->GetLayer(iLayerIdx);

	pCurLayer->RegisterCollider(this);

}

void CCollider::render(HDC _dc)
{
	if (!DEBUG_RENDER)
		return;

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vFinalPos);

	if (m_iCollisionCount > 0)
	{
		SELECT_PEN(_dc, PEN_TYPE::RED);

		// render
		Rectangle(_dc, int(vRenderPos.x - m_vScale.x / 2.f)
			, int(vRenderPos.y - m_vScale.y / 2.f)
			, int(vRenderPos.x + m_vScale.x / 2.f)
			, int(vRenderPos.y + m_vScale.y / 2.f));
	}
	else
	{
		SELECT_PEN(_dc, PEN_TYPE::GREEN);

		// render
		Rectangle(_dc, int(vRenderPos.x - m_vScale.x / 2.f)
			, int(vRenderPos.y - m_vScale.y / 2.f)
			, int(vRenderPos.x + m_vScale.x / 2.f)
			, int(vRenderPos.y + m_vScale.y / 2.f));
	}
}


void CCollider::BeginOverlap(CCollider* _pOtherCol)
{
	++m_iCollisionCount;
	GetOwner()->BeginOverlap(this, _pOtherCol->GetOwner(), _pOtherCol);
}

void CCollider::Overlap(CCollider* _pOtherCol)
{
	GetOwner()->Overlap(this, _pOtherCol->GetOwner(), _pOtherCol);
}

void CCollider::EndOverlap(CCollider* _pOtherCol)
{
	--m_iCollisionCount;
	GetOwner()->EndOverlap(this, _pOtherCol->GetOwner(), _pOtherCol);
}
