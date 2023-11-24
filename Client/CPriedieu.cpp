#include "pch.h"
#include "CPriedieu.h"

#include "CKeyMgr.h"
#include "CAssetMgr.h"
#include "CTexture.h"

#include "CPenitent.h"

CPriedieu::CPriedieu()
	: m_pAnimator(nullptr)
	, m_pCollider(nullptr)
	, isPopup(false)
{
	// Animator 持失
	m_pAnimator = AddComponent<CAnimator>();

	m_pPopupTex = CAssetMgr::GetInst()->LoadTexture(L"SpacePopup", L"texture\\UI\\KB_SPACE.png");

	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"Priedieu", L"texture\\Object\\MetaObject\\priedieu_upgrade2_stand_and_liton_anim.png");
	m_pAnimator->LoadAnimation(pTex, L"Priedieu", L"animdata\\Object\\priedieu_upgrade2_stand_and_liton_anim.txt");
	m_pAnimator->SetAnimDuration(L"Priedieu", 0.1f);

	m_pAnimator->Play(L"Priedieu", true);


	// Collider 持失
	m_pCollider = AddComponent<CCollider>();
	m_pCollider->SetScale(Vec2(20.f, 100.f));
	m_pCollider->SetOffsetPos(Vec2(0.f, -40.f));
}

CPriedieu::~CPriedieu()
{
}


void CPriedieu::render(HDC _dc)
{
	Super::render(_dc);

	if (isPopup)
	{
		Vec2 vRenderPos = GetRenderPos();
		Vec2 vScale = GetScale();
		Vec2 vSize = Vec2(m_pPopupTex->GetWidth(), m_pPopupTex->GetHeight());


		BLENDFUNCTION blend = {};
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;

		blend.SourceConstantAlpha = 255; // 0 ~ 255
		blend.AlphaFormat = AC_SRC_ALPHA; // 0

		AlphaBlend(_dc
			, int(vRenderPos.x - vSize.x / 2.f - 20.f)
			, int(vRenderPos.y - 200.f)
			, int(vSize.x * GetScale().x)
			, int(vSize.y * GetScale().y)
			, m_pPopupTex->GetDC()
			, 0, 0
			, int(vSize.x)
			, int(vSize.y)
			, blend);
	}
	
}

void CPriedieu::Overlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol)
{
	if (_pOtherObj->GetLayerIdx() != (UINT)LAYER::PLAYER)
		return;

	CPenitent* pPenitent = dynamic_cast<CPenitent*>(_pOtherObj);
	CStateMachine* pSM = pPenitent->GetComponent<CStateMachine>();

	if (pSM->GetCurState() != (UINT)PENITENT_STATE::PRAYSTART && pSM->GetCurState() != (UINT)PENITENT_STATE::PRAYING
		&& pSM->GetCurState() != (UINT)PENITENT_STATE::PRAYAURAOFF && pSM->GetCurState() != (UINT)PENITENT_STATE::PRAYEND)
	{
		isPopup = true;
	}
	else
	{
		isPopup = false;
	}

	if (KEY_TAP(KEY::SPACE))
	{
		pSM->ChangeState((UINT)PENITENT_STATE::PRAYSTART);
	}

}

void CPriedieu::EndOverlap(CCollider* _pOwnCol, CObj* _pOtherObj, CCollider* _pOtherCol)
{
	isPopup = false;
}
