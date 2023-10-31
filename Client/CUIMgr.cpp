#include "pch.h"
#include "CUIMgr.h"

#include "CKeyMgr.h"
#include "CLevelMgr.h"

#include "CLevel.h"
#include "CUI.h"

CUIMgr::CUIMgr()
	: m_pFocusedUI(nullptr)
{
}

CUIMgr::~CUIMgr()
{
}


void CUIMgr::tick()
{
	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
	bool bLBtnTap = KEY_TAP(KEY::LBTN);
	bool bLBtnReleased = KEY_RELEASED(KEY::LBTN);


	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	if (nullptr == pCurLevel)
		return;


	CLayer* pUILayer = pCurLevel->GetLayer((UINT)LAYER::UI);
	vector<CObj*>& vecUI = pUILayer->m_vecObjects;
	vector<CObj*>::reverse_iterator iter = vecUI.rbegin();
	
	for (iter; iter != vecUI.rend(); ++iter)
	{
		CUI* pUI = dynamic_cast<CUI*>(*iter);
		if (nullptr == pUI)
		{
			LOG(LOG_LEVEL::ERR, L"UI Layer에 UI가 아닌 오브젝트가 들어있습니다.");
			continue;
		}

		if (pUI->m_bMouseOn)
		{
			m_pFocusedUI = pUI;

			pUI = GetPriorityCheck(pUI);

			if (pUI->m_bMouseOn_Prev != pUI->m_bMouseOn)
			{
				pUI->OnHovered(vMousePos);
			}
			else
			{
				pUI->MouseOn(vMousePos);
			}
			
			if (bLBtnReleased)
			{
				pUI->LBtnUp(vMousePos);

				if (pUI->m_bMouseLBtnDown)
				{
					pUI->LBtnClicked(vMousePos);
				}
			}

			if (bLBtnTap)
			{
				pUI->LBtnDown(vMousePos);
				pUI->m_bMouseLBtnDown = true;

				std::advance(iter, 1);
				vecUI.erase(iter.base());

				vecUI.push_back(m_pFocusedUI);
			}

			if (bLBtnReleased)
			{
				pUI->m_bMouseLBtnDown = false;
			}

			break;

		}
		else
		{
			if (pUI->m_bMouseOn_Prev != pUI->m_bMouseOn)
			{
				pUI->OnUnHovered(vMousePos);
			}

			if (bLBtnReleased)
			{
				pUI->m_bMouseLBtnDown = false;
			}
		}
		
	}


}

CUI* CUIMgr::GetPriorityCheck(CUI* _pParentUI)
{
	CUI* pPriorityUI = nullptr;

	static list<CUI*> queue;

	queue.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		CUI* pUI = queue.front();
		queue.pop_front();

		for (size_t i = 0; i < pUI->m_vecChildUI.size(); ++i)
		{
			queue.push_back(pUI->m_vecChildUI[i]);
		}

		if (pUI->m_bMouseOn)
		{
			pPriorityUI = pUI;
		}
	}


	return pPriorityUI;
}
