#pragma once

#include<WICTextureLoader.h>
#include<d3d11.h>

using namespace DirectX;

class Texture
{
public:
    static ID3D11ShaderResourceView* load( const wchar_t* FileName );
};