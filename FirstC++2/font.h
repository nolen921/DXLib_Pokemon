#pragma once

// Include
#include <SpriteFont.h>
#include <SimpleMath.h>
#include "direct3d.h"
#include "sprite.h"
#include "error.h"

// Namespace
using namespace DirectX;
using namespace SimpleMath;

// Class
class Font
{
private:
    static SpriteFont* font_;   // �X�v���C�g�t�H���g�N���X

public:
    static bool init();     // ������
    static void destroy();  // �j��
    static void draw( const wchar_t* String, const Vector2& Position ); // �`��
};