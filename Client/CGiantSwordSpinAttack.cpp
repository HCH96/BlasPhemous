#include "pch.h"
#include "CGiantSwordSpinAttack.h"

#include "CLevelMgr.h"
#include "CPenitent.h"


CGiantSwordSpinAttack::CGiantSwordSpinAttack()
	: m_vTarget(Vec2(0.f,0.f))
	, m_vInitPos(Vec2 (0.f,0.f))
{
}

CGiantSwordSpinAttack::~CGiantSwordSpinAttack()
{
}

void CGiantSwordSpinAttack::finaltick(float _DT)
{
	m_fAcc += _DT;

	CObj* pOwner = GetOwnerObj;

	float fAngle = pOwner->GetAngle();
	Vec2 vPos = pOwner->GetPos();
	Vec2 vDir = (m_vTarget - m_vInitPos).Normalize();

	float fSpeed = (m_vTarget - m_vInitPos).Length() *1.3f;


	// Player가 오른쪽에있는 경우
	if (m_vTarget.x - m_vInitPos.x > 0)
	{
		fAngle = fAngle - 360.f * _DT;
		vPos += vDir * fSpeed * _DT;

	}
	// Player가 왼쪽에 있는 경우
	else
	{
		fAngle = fAngle + 360.f * _DT;
		vPos += vDir * fSpeed * _DT;
	}

	pOwner->SetAngle(fAngle);
	pOwner->SetPos(vPos);


	if (m_fAcc > 1.25f)
	{
		GetOwnerSM()->ChangeState((UINT)GIANTSWORD::IDLE);
	}


}

void CGiantSwordSpinAttack::Enter()
{

	CObj* pOwner = GetOwnerObj;
	m_vInitPos = pOwner->GetPos();
	m_vTarget = CLevelMgr::GetInst()->GetPenitent()->GetPos();
	m_vTarget.y = m_vTarget.y - 200.f;

	CCollider* pCollider = pOwner->GetComponent<CCollider>();
	pCollider->SetScale(Vec2(40.f, 230.f));
	pCollider->SetOffsetPos(Vec2(0.f, 90.f));


	if ((m_vTarget - m_vInitPos).Length() > 600.f)
	{
		m_vInitPos = m_vTarget + Vec2(200.f, -200.f);
		pOwner->SetPos(m_vInitPos);
	}


	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"SWORD_AIR_ATTACK", L"sound\\Object\\Monster\\Boss\\Pontiff\\SWORD_AIR_ATTACK.wav");
	pSound->Play();

	m_fAcc = 0.f;

	m_bSound = false;

}

void CGiantSwordSpinAttack::Exit()
{
	CObj* pOwner = GetOwnerObj;
	CCollider* pCollider = pOwner->GetComponent<CCollider>();
	pCollider->SetScale(Vec2(40.f, 40.f));
	pCollider->SetOffsetPos(Vec2(0.f, 0.f));
}

