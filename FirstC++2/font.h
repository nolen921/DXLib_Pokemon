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
    static SpriteFont* font_;   // スプライトフォントクラス

public:
    static bool init();     // 初期化
    static void destroy();  // 破棄
    static void draw( const wchar_t* String, const Vector2& Position ); // 描画
};