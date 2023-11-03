#include "pch.h"
#include "CAssetMgr.h"

#include "CEngine.h"

#include "CPathMgr.h"
#include "CTexture.h"
#include "CSound.h"

CAssetMgr::CAssetMgr()
{
}

CAssetMgr::~CAssetMgr()
{
	for (const auto& pair : m_mapTex)
	{
		delete pair.second;
	}

	for (const auto& pair : m_mapSound)
	{
		delete pair.second;
	}
}

CTexture* CAssetMgr::FindTexture(const wstring& _strKey)
{
	map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey);

	if (m_mapTex.end() == iter)
	{
		return nullptr;
	}

	return iter->second;
}

CTexture* CAssetMgr::CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight)
{
	CTexture* pTexture = FindTexture(_strKey);

	if (nullptr != pTexture)
	{
		return pTexture;
	}

	pTexture = new CTexture;
	pTexture->Create(_iWidth, _iHeight);

	pTexture->m_strKey = _strKey;

	m_mapTex.insert(make_pair(_strKey, pTexture));

	return pTexture;
}

CTexture* CAssetMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	CTexture* pTexture = FindTexture(_strKey);

	if (nullptr != pTexture)
	{
		return pTexture;	
	}

	wstring strContentPath = CPathMgr::GetContentDirectory();
	strContentPath += _strRelativePath;

	pTexture = new CTexture;
	if (!pTexture->Load(strContentPath))
	{
		delete pTexture;
		return nullptr;
	}

	pTexture->m_strKey = _strKey;
	pTexture->m_strRelativePath = _strRelativePath;

	m_mapTex.insert(make_pair(_strKey, pTexture));

	return pTexture;
}

CTexture* CAssetMgr::LoadTextureReverse(const wstring& _strKey, const wstring& _strRelativePath)
{
	CTexture* pTexture = FindTexture(_strKey);

	if (nullptr != pTexture)
	{
		return pTexture;
	}

	wstring strContentPath = CPathMgr::GetContentDirectory();
	strContentPath += _strRelativePath;

	pTexture = new CTexture;
	if (!pTexture->Load_r(strContentPath))
	{
		delete pTexture;
		return nullptr;
	}

	pTexture->m_strKey = _strKey;
	pTexture->m_strRelativePath = _strRelativePath;

	m_mapTex.insert(make_pair(_strKey, pTexture));

	return pTexture;
}


CSound* CAssetMgr::LoadSound(const wstring& _strKey, const wstring& _strRelativePath)
{
	// 입력된 키에 해당하는 텍스쳐가 있는지 확인한다.
	CSound* pSound = FindSound(_strKey);
	if (nullptr != pSound)
	{
		// 이미 있는 텍스쳐면 찾은걸 반환해준다.
		return pSound;
	}

	// 입력된 키에 해당하는 텍스쳐가 없으면 로딩해서 반환해준다.
	wstring strContentPath = CPathMgr::GetContentDirectory();
	wstring strFilePath = strContentPath + _strRelativePath;

	pSound = new CSound;

	if (!pSound->Load(strFilePath))
	{
		// 텍스쳐 로드가 실패한 경우(경로 문제 등등..)
		delete pSound;
		return nullptr;
	}

	// Asset 에 키값과 경로값을 알려준다.
	pSound->m_strKey = _strKey;
	pSound->m_strRelativePath = _strRelativePath;

	m_mapSound.insert(make_pair(_strKey, pSound));

	return pSound;
}

CSound* CAssetMgr::FindSound(const wstring& _strKey)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(_strKey);

	if (iter == m_mapSound.end())
	{
		return nullptr;
	}

	return iter->second;
}
