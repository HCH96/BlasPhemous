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
	CTexture* FindTexture(const wstring& _strKey);
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);

};

