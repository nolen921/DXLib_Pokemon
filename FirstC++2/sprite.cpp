#include "sprite.h"
#include "direct3d.h"
#include "common.h"

SpriteBatch* Sprite::sprite_;

bool Sprite::init()
{
    sprite_ = new SpriteBatch( Direct3D::getContext() );

    if( !sprite_ )
    {
        return false;
    }

    return true;
}

void Sprite::begin()
{
    sprite_->Begin( SpriteSortMode_Deferred, Common::getState()->NonPremultiplied() );  /* 中のアルファ宣言により、透明化 */
}

void Sprite::draw(
    ID3D11ShaderResourceView* Texture,  // テクスチャ
    const Vector2& Position,            // 座標
    const RECT* Rect,                   // 描画範囲
    const float Rotation,               // 回転
    const Vector2& Scale,               // 拡縮
    const Vector2& Origin,              // アンカーポイント
    const SpriteEffects Effect,         // エフェクト,
    const float Depth )                 // 深度
{
    sprite_->Draw(
        Texture,                // テクスチャ
        Position,               // 座標
        Rect,                   // 描画範囲
        Colors::White,          // カラー
        Rotation,               // 回転値   0.0F * XM_PI / 180.0F
        Origin,                 // アンカーポイント（原点）
        Scale,                  // 拡縮
        Effect,                 // エフェクト
        Depth );                // 深度値
}