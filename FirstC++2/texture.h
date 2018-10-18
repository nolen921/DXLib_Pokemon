#pragma once

#include<d3d11.h>

using namespace DirectX;

class Texture
{
public:
    // static int num_;

    static ID3D11ShaderResourceView* load( const wchar_t* FileName, ID3D11Device* Device, ID3D11DeviceContext* Context );
};