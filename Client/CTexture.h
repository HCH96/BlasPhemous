#pragma once
#include "CAsset.h"
class CTexture :
    public CAsset
{
private:
    HBITMAP         m_hBit;
    HDC             m_hDC;
    BITMAP          m_Info;

public:
    HDC GetDC() { return m_hDC; }
    HBITMAP GetBitmap() { return m_hBit; }
    UINT GetWidth() { return m_Info.bmWidth; }
    UINT GetHeight() { return m_Info.bmHeight; }

private:
    void Create(UINT _iWidth, UINT _iHeight);
    virtual bool Load(const wstring& _strFilePath) override;


private:
    CTexture();
    ~CTexture();

    friend class CAssetMgr;
};

