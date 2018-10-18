#include"player.h"
#include"texture.h"

// コンストラクタ
Player::Player()
{
    // メンバ変数初期化
    position_.x = static_cast<float>(rand() % 1280);
    position_.y = static_cast<float>(rand() % 720);
    speed_ = static_cast<float>(rand() % 10) + 2.0F;
}

// デストラクタ
Player::~Player()
{

}

bool Player::init( const wchar_t* FileName, ID3D11Device* Device, ID3D11DeviceContext* Context )
{
    // 
    // loadをstaticにするといらない　→　Texture tex;
    texture_ = Texture::load( FileName, Device, Context );

    if( texture_ == NULL )
    {
        // エラー
        return false;
    }

    /*
    Texture::num_ = 100;    // staticメンバ変数かつ実体を作ったのでここでも使える

    Texture tex;

    tex.num_ = 200;
    */

    // メンバ変数初期化
    position_.x = static_cast<float>(rand() % 1280);
    position_.y = static_cast<float>(rand() % 720);
    speed_ = static_cast<float>(rand() % 10) + 2.0F;

    return true;
}

// 更新処理
void Player::update()
{
    // 移動
    position_.x += speed_;

    if( position_.x > 1280.0F )
    {
        position_.x = -64.0F;
    }
}

// 描画
void Player::draw( SpriteBatch* Sprite )
{
    // 描画範囲の設定
    RECT rect;
    rect.top = 0L;
    rect.left = 0L;
    rect.right = 64L;
    rect.bottom = 64L;

    static float rotate = 0.0F;
    rotate++;
    

    Sprite->Draw(
        texture_,           // テクスチャ
        position_,          // 座標
        &rect,              // 描画範囲
        Colors::Red,        // カラー
        rotate * XM_PI / 180.0F,               // 回転値
        Vector2(32.0F,32.0F), // アンカーポイント（原点）
        Vector2(1.0F,1.0F), // 拡縮
        SpriteEffects_None, // エフェクト
        0.0F                // 深度値
    );
}

// 破棄
void Player::destroy()
{
    texture_->Release();
}
