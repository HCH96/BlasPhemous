#include "pch.h"
#include "CGCMgr.h"


#include "CEntity.h"

CGCMgr::CGCMgr()
{

}


CGCMgr::~CGCMgr()
{
	for (size_t i = 0; i < m_vecEntity.size(); ++i)
	{
		if (m_vecEntity[i] != nullptr)
		{
			delete m_vecEntity[i];
		}
	}

}


void CGCMgr::tick()
{
	if (m_vecEntity.size() < 10)
	{
		return;
	}

	for (size_t i = 0; i < m_vecEntity.size(); ++i)
	{
		if (m_vecEntity[i] != nullptr)
		{
			delete m_vecEntity[i];
		}
	}

	m_vecEntity.clear();
}
