#include "pch.h"
#include "CCage.h"

#include "CAssetMgr.h"
#include "CTexture.h"



CCage::CCage()
	: m_pAnimator(nullptr)
	, m_pCollider(nullptr)
{
	// Animator
	m_pAnimator = AddComponent<CAnimator>(L"Cage");
	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"Cage", L"texture\\Object\\reja_lateral_invertedBell_descending.png");

	m_pAnimator->LoadAnimation(pTex, L"CageUp", L"animdata\\Object\\CageUp.txt",true);
	m_pAnimator->SetAnimDuration(L"CageUp", 0.1f);

	m_pAnimator->LoadAnimation(pTex, L"CageOpen", L"animdata\\Object\\CageOpen.txt", true);
	m_pAnimator->SetAnimDuration(L"CageOpen", 0.1f);

	m_pAnimator->LoadAnimation(pTex, L"CageDown", L"animdata\\Object\\CageDown.txt", true);
	m_pAnimator->SetAnimDuration(L"CageDown", 0.1f);

	m_pAnimator->Play(L"CageDown", true);


	// Collider
	m_pCollider = AddComponent<CCollider>(L"Cage");
	m_pCollider->SetScale(Vec2(80.f, 250.f));
	m_pCollider->SetOffsetPos(Vec2(0.f, 140.f));

}

CCage::~CCage()
{
}


void CCage::Open()
{
	m_pAnimator->Play(L"CageOpen", false);
	m_pCollider->Off();
}

void CCage::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if (_OtherObj->GetLayerIdx() != (UINT)LAYER::PLAYER)
		return;

	Vec2 vPos = _OwnCol->GetPos();
	Vec2 vObjPos = _OtherObj->GetPos();
	CMovement* pOtherMovement = _OtherObj->GetComponent<CMovement>();

	if (m_pCollider->GetAngle() == 0.f)
	{
		// 왼쪽으로 충돌했을 경우
		if (vPos.x > vObjPos.x && (pOtherMovement->GetVelocity().x > 0))
		{
			_OtherObj->SetPos(Vec2(vPos.x - _OwnCol->GetScale().x / 2.f - _OtherCol->GetScale().x / 2.f, vObjPos.y));
		}

		// 오른쪽으로 충돌했을 경우
		if (vPos.x < vObjPos.x && (pOtherMovement->GetVelocity().x < 0))
		{
			_OtherObj->SetPos(Vec2(vPos.x + _OwnCol->GetScale().x / 2.f + _OtherCol->GetScale().x / 2.f, vObjPos.y));
		}
	}
}