#pragma once
#include "CEntity.h"
class CAsset :
    public CEntity
{
private:
    wstring     m_strKey;
    wstring     m_strRelativePath;

public:
    const wstring& GetKey() { return m_strKey; }
    const wstring& GetRelativePath() { return m_strRelativePath; }


private:
    virtual bool Load(const wstring& _strFilePath) = 0;

public:
    CAsset();
    ~CAsset();

    friend class CAssetMgr;
};

