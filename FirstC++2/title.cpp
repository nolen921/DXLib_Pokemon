#include "title.h"
#include "texture.h"
#include "sprite.h"
#include "key.h"

// 初期化
bool Title::init()
{
    // テクスチャの読み込み
    if( !(texture_ = Texture::load( L"pokemon_rse2.png" )) )
    {
        // エラー
        return false;
    }

    return true;
}

// 更新
bool Title::update()
{
    const Keyboard::State key = Key::getState();

    // スペースキーが押されたらタイトル画面終了
    if( key.Space )
    {
        return false;
    }

    return true;
}

// 描画
void Title::draw()
{
    Sprite::draw( texture_, Vector2::Zero );
}

// 破棄
void Title::destroy()
{
    // テクスチャの解放
    SAFE_RELEASE( texture_ );
}