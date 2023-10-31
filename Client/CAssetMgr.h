#pragma once

class CSound;
class CTexture;


class CAssetMgr
{
	SINGLETON(CAssetMgr);

private:
	map<wstring, CTexture*>		m_mapTex;
	map<wstring, CSound*>		m_mapSound;

public:
	CSound* LoadSound(const wstring& _strKey, const wstring& _strRelativePath);
	CSound* FindSound(const wstring& _strKey);

	CTexture* FindTexture(const wstring& _strKey);
	CTexture* CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight);
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);

};

