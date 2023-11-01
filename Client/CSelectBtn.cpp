#include "pch.h"
#include "CSelectBtn.h"

#include "resource.h"
#include "CEngine.h"

#include "CKeyMgr.h"
#include "CAssetMgr.h"

CSelectBtn::CSelectBtn()
	: m_pNormalImg(nullptr)
	, m_pCallBackFunc(nullptr)
	, m_pInst(nullptr)
	, m_pDelegate(nullptr)
{
}

CSelectBtn::~CSelectBtn()
{
}

void CSelectBtn::SetNormalImg(const wstring& _strKey)
{
	m_pNormalImg = CAssetMgr::GetInst()->FindTexture(_strKey);

}

void CSelectBtn::SetSelectImg(const wstring& _strKey)
{
	m_pSelectImg = CAssetMgr::GetInst()->FindTexture(_strKey);
}

void CSelectBtn::tick(float _DT)
{

	// component tick -> ChildUI tick
	Super::tick(_DT);
}

void CSelectBtn::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	if (m_bSelect)
	{
		// select Img ���
		AlphaBlendRender(_dc, m_pSelectImg, vPos, vScale);
	}
	else
	{
		// Normal Img ���
		AlphaBlendRender(_dc, m_pNormalImg, vPos, vScale);
	}


	// �θ�Ŭ����(CUI) �����Լ� ȣ��(�ڽ� UI ������ render �� ȣ���Ѵ�)
	// Component render -> ChildUI render
	Super::render(_dc);

}

void CSelectBtn::Select()
{
	if (nullptr != m_pCallBackFunc)
	{
		m_pCallBackFunc();
	}

	if (nullptr != m_pInst && nullptr != m_pDelegate)
	{
		(m_pInst->*m_pDelegate)();
	}
}