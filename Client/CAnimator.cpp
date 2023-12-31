#include "pch.h"
#include "CAnimator.h"

#include "CPathMgr.h"

#include "CAnim.h"

CAnimator::CAnimator(CObj* _Owner)
	: CComponent(_Owner)
	, m_pCurAnim(nullptr)
	, m_bRepeat(false)
	, m_iAlpha(255)
	, m_fAcc(0.f)
	, m_bPosLock(false)
{
}

CAnimator::CAnimator(const CAnimator& _Origin)
	: CComponent(_Origin)
	, m_pCurAnim(nullptr)
	, m_bRepeat(_Origin.m_bRepeat)
	, m_iAlpha(_Origin.m_iAlpha)
	, m_fAcc(_Origin.m_fAcc)

{
	for (const auto& pair : _Origin.m_mapAnim)
	{
		CAnim* pAnim = pair.second->Clone();
		pAnim->m_pAnimator = this;
		m_mapAnim.insert(make_pair(pair.first, pAnim));
	}

	if (nullptr != _Origin.m_pCurAnim)
	{
		m_pCurAnim = FindAnimation(_Origin.m_pCurAnim->GetName());
	}

}

CAnimator::~CAnimator()
{
	for (const auto& pair : m_mapAnim)
	{
		delete pair.second;
	}
}

void CAnimator::finaltick(float _DT)
{
	if (IsValid(m_pCurAnim))
	{
		if (m_bRepeat && m_pCurAnim->IsFinish())
		{
			m_pCurAnim->Reset();
		}

		m_pCurAnim->finaltick(_DT);
	}
}

void CAnimator::render(HDC _dc)
{
	if (IsValid(m_pCurAnim))
	{
		m_pCurAnim->render(_dc);
	}

}

bool CAnimator::IsFinish()
{
	if (m_pCurAnim == nullptr)
		return false;

	return m_pCurAnim->IsFinish();
}

int CAnimator::GetCurFrame()
{
	return m_pCurAnim->m_iCurFrm;
}

void CAnimator::SetFrame(int _i)
{
	m_pCurAnim->SetFrame(_i);
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	m_bRepeat = _bRepeat;
	m_pCurAnim = FindAnimation(_strName);

	m_pCurAnim->Reset();

	assert(m_pCurAnim);
}

void CAnimator::PlayNoReset(const wstring& _strName, bool _bRepeat)
{
	m_bRepeat = _bRepeat;
	m_pCurAnim = FindAnimation(_strName);

	assert(m_pCurAnim);
}

void CAnimator::PlayFromFrame(const wstring& _strName, UINT _iFrame, bool _bRepeat)
{
	m_bRepeat = _bRepeat;
	m_pCurAnim = FindAnimation(_strName);

	if (m_pCurAnim->m_vecFrm.size() > _iFrame)
	{
		m_pCurAnim->m_iCurFrm = _iFrame;
		m_pCurAnim->m_fAccTime = 0.f;
		m_pCurAnim->m_bFinish = false;
	}
	else
	{
		LOG(LOG_LEVEL::WARNING, L"!!인자로 받은 Frame이 MaxFrame보다 큽니다!!");
	}
	assert(m_pCurAnim);
}

void CAnimator::Stop()
{
	m_pCurAnim->Reset();
	m_pCurAnim = nullptr;
}



void CAnimator::SetAnimDuration(const wstring& _strName, float _fDuration)
{
	CAnim* pAnim = FindAnimation(_strName);

	if (pAnim == nullptr)
	{
		LOG(LOG_LEVEL::ERR, L"Anim을 찾지 못했습니다.");
		return;
	}
	
	for (size_t i = 0; i < pAnim->m_vecFrm.size(); ++i)
	{
		pAnim->SetDuration(_fDuration, int(i));
	}

}

void CAnimator::SetAnimOffset(const wstring& _strName, Vec2 _vOffset)
{
	CAnim* pAnim = FindAnimation(_strName);

	if (pAnim == nullptr)
	{
		LOG(LOG_LEVEL::ERR, L"Anim을 찾지 못했습니다.");
		return;
	}

	for (size_t i = 0; i < pAnim->m_vecFrm.size(); ++i)
	{
		pAnim->SetOffset(_vOffset, int(i));
	}

}

void CAnimator::FixAnimOffset(const wstring& _strName, Vec2 _vOffset)
{
	CAnim* pAnim = FindAnimation(_strName);

	if (pAnim == nullptr)
	{
		LOG(LOG_LEVEL::ERR, L"Anim을 찾지 못했습니다.");
		return;
	}

	for (size_t i = 0; i < pAnim->m_vecFrm.size(); ++i)
	{
		pAnim->FixOffset(_vOffset, int(i));
	}

}


void CAnimator::SetAnimDuration(const wstring& _strName, UINT _iFrame, float _fDuration)
{
	CAnim* pAnim = FindAnimation(_strName);

	if (pAnim == nullptr)
	{
		LOG(LOG_LEVEL::ERR, L"Anim을 찾지 못했습니다.");
		return;
	}

	pAnim->SetDuration(_fDuration, int(_iFrame));

}



void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _pAtlas, Vec2 _vLeftTop, Vec2 _vCutSize, Vec2 _vOffset, float _fDuration, int _iMaxFrm)
{
	CAnim* pAnim = FindAnimation(_strName);

	if (IsValid(pAnim))
	{
		return;
	}

	pAnim = new CAnim;
	pAnim->m_pAnimator = this;
	pAnim->Create(_strName, _pAtlas, _vLeftTop, _vCutSize, _vOffset, _fDuration, _iMaxFrm);
	m_mapAnim.insert(make_pair(_strName, pAnim));
}


CAnim* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnim*>::iterator iter = m_mapAnim.find(_strName);

	if (iter == m_mapAnim.end())
	{
		return nullptr;
	}

	return iter->second;
}

void CAnimator::SaveAnimations(const wstring& _strRelativePath)
{
	wstring strFolderPath = CPathMgr::GetContentDirectory();
	strFolderPath += _strRelativePath;

	for (const auto& pair : m_mapAnim)
	{
		wstring strFilePath = strFolderPath + L"\\" + pair.first + L".txt";
		if (!pair.second->Save(strFilePath))
		{
			LOG(LOG_LEVEL::ERR, L"Animation Save 실패");
		}
	}
}

void CAnimator::LoadAnimation(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetContentDirectory();
	strFilePath += _strRelativePath;

	CAnim* pNewAnim = new CAnim;

	if (!pNewAnim->Load(strFilePath))
	{
		LOG(LOG_LEVEL::ERR, L"Animation Load 실패");
		delete pNewAnim;
		return;
	}

	pNewAnim->m_pAnimator = this;
	m_mapAnim.insert(make_pair(pNewAnim->GetName(), pNewAnim));

}

void CAnimator::LoadAnimation(CTexture* _pTexture, const wstring& _strAnimKey, const wstring& _strMetaRelativePath, bool _bReverse)
{
	if (_pTexture == nullptr)
	{
		assert(nullptr);
	}

	wstring strFilePath = CPathMgr::GetContentDirectory();
	strFilePath += _strMetaRelativePath;

	CAnim* pNewAnim = new CAnim;

	if (!_bReverse)
	{
		if (!pNewAnim->LoadMeta(_pTexture, _strAnimKey, strFilePath))
		{
			LOG(LOG_LEVEL::ERR, L"Animation Load 실패");
			delete pNewAnim;
			return;
		}
	}
	else
	{
		if (!pNewAnim->LoadMetaReverse(_pTexture, _strAnimKey, strFilePath))
		{
			LOG(LOG_LEVEL::ERR, L"Animation Load 실패");
			delete pNewAnim;
			return;
		}
	}

	

	pNewAnim->m_pAnimator = this;
	m_mapAnim.insert(make_pair(_strAnimKey, pNewAnim));

}

