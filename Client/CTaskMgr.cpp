#include "pch.h"
#include "CTaskMgr.h"

#include "CObj.h"
#include "CLevelMgr.h"
#include "CLevel.h"


CTaskMgr::CTaskMgr()
{
}

CTaskMgr::~CTaskMgr()
{
}


void CTaskMgr::tick()
{
	for (size_t i = 0; i < m_vecTask.size(); i++)
	{
		switch (m_vecTask[i].Type)
		{
		case TASK_TYPE::CREATE_OBJECT:
		{
			LAYER eLayerType = (LAYER)m_vecTask[i].Param_1;
			CObj* pObject = (CObj*)m_vecTask[i].Param_2;

			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

			pCurLevel->AddObject(eLayerType, pObject);
			pObject->begin();
		}

			break;
		case TASK_TYPE::DELETE_OBJECT:
		{
			CObj* pDeadObj = (CObj*)m_vecTask[i].Param_1;
			pDeadObj->SetDead();
		}

			break;
		case TASK_TYPE::LEVEL_CHANGE:
		{
			LEVEL_TYPE eType = (LEVEL_TYPE)m_vecTask[i].Param_1;
			CLevelMgr::GetInst()->ChangeLevel(eType);
		}
			break;
		case TASK_TYPE::END:
		{

		}
			break;
		}
	}

	m_vecTask.clear();

}
