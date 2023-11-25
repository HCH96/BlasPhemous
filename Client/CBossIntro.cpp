#include "pch.h"
#include "CBossIntro.h"


#include "CLevelMgr.h"
#include "CLevel.h"

CBossIntro::CBossIntro()
	: m_pCollider(nullptr)
{
	m_pCollider = AddComponent<CCollider>(L"BossIntro");
	m_pCollider->SetScale(Vec2(100.f, 100.f));

}

CBossIntro::~CBossIntro()
{
}


void CBossIntro::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	pCurLevel->BossIntro();


	m_pCollider->SetTime(0.f);
}


