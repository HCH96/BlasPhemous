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
	, m_fAngle(0.f)
	, m_bOn(true)
	, m_fDuration(-1.f)
	, m_fAcc(0.f)
{
}

CCollider::CCollider(const CCollider& _Origin)
	: CComponent(_Origin)
	, m_vOffsetPos(_Origin.m_vOffsetPos)
	, m_vScale(_Origin.m_vScale)
	, m_vFinalPos(_Origin.m_vFinalPos)
	, m_iCollisionCount(0)
	, m_bOn(_Origin.m_bOn)
	, m_fDuration(_Origin.m_fDuration)
	, m_fAcc(_Origin.m_fAcc)
{
}

CCollider::~CCollider()
{
}

void CCollider::finaltick(float _DT)
{
	// 좌표 값 수정
	Vec2 vOwnerPos = GetOwner()->GetPos();
	m_vFinalPos = vOwnerPos + m_vOffsetPos;
	m_fAngle = GetOwner()->GetAngle();

	// 현재 속해있는 레이어에 충돌체(본인) 를 등록

	int iLayerIdx = GetOwner()->GetLayerIdx();
	assert(!(iLayerIdx < 0));

	CLayer* pCurLayer = CLevelMgr::GetInst()->GetCurLevel()->GetLayer(iLayerIdx);


	if(m_bOn)
		pCurLayer->RegisterCollider(this);

	// Collider Duration Check

	// Duration을 사용하지 않는 Collider, Off 상태인 콜라이더
	if (m_fDuration == -1.f || !m_bOn)
		return;

	m_fAcc += _DT;
	
	if (m_fAcc > m_fDuration)
	{
		m_bOn = false;
		m_fAcc = 0.f;
	}
}

void CCollider::render(HDC _dc)
{
	if (!DEBUG_RENDER)
		return;
	if (!m_bOn)
		return;

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vFinalPos);

	if (m_iCollisionCount > 0)
	{
		SELECT_PEN(_dc, PEN_TYPE::RED);

		// render
		DrawRotatedRectangle(_dc, (int)vRenderPos.x, (int)vRenderPos.y, (int)m_vScale.x, (int)m_vScale.y, m_fAngle);

		//Rectangle(_dc, int(vRenderPos.x - m_vScale.x / 2.f)
		//	, int(vRenderPos.y - m_vScale.y / 2.f)
		//	, int(vRenderPos.x + m_vScale.x / 2.f)
		//	, int(vRenderPos.y + m_vScale.y / 2.f));
	}
	else
	{
		SELECT_PEN(_dc, PEN_TYPE::GREEN);

		DrawRotatedRectangle(_dc, (int)vRenderPos.x, (int)vRenderPos.y, (int)m_vScale.x, (int)m_vScale.y, m_fAngle);
		// render
		//Rectangle(_dc, int(vRenderPos.x - m_vScale.x / 2.f)
		//	, int(vRenderPos.y - m_vScale.y / 2.f)
		//	, int(vRenderPos.x + m_vScale.x / 2.f)
		//	, int(vRenderPos.y + m_vScale.y / 2.f));
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
