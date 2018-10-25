#include"player.h"
#include"texture.h"
#include"sprite.h"

/* pokemon_charの大きさ */
int kPlayertop = 0L;
int kPlayersizeX = 64L;
int kPlayersizeY = 96L;

const int haruka = 256;
const int hakase = 384;

// コンストラクタ
Player::Player()
{
    // メンバ変数初期化
    // position_.x = static_cast<float>(rand() % 1280);
    // position_.y = static_cast<float>(rand() % 720);
    // speed_ = static_cast<float>(rand() % 10) + 2.0F;
    position_.x = 608.0F;
    position_.y = 296.0F;
    speed_ = 4.0F;
    animation_no_ = 0;
    animation_counter_ = 0;
    rect.top = 0L;
    rect.left = 0L;
    rect.right = 64L;
    rect.bottom = 96L;
    direction_ = 0;
}

// デストラクタ
Player::~Player()
{

}

bool Player::init( const wchar_t* FileName )
{
    // loadをstaticにするといらない　→　Texture tex;
    texture_ = Texture::load( FileName );

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

    return true;
}

void Player::animation()
{
    if( animation_counter_ >= 12 )
    {
        animation_counter_ = 0;
        animation_no_++;
        if( animation_no_ > 3 )
            animation_no_ = 0;
    }
    animation_counter_++;
}

// 更新処理
void Player::update( const Keyboard::State* pState )
{
    // ↓が押されたか
    if( pState->Down )
    {
        direction_ = 0;
        position_.y += 4.0F;
    }

    // ↑が押されたか
    if( pState->Up )
    {
        direction_ = 1;
        position_.y -= 4.0F;
    }

    // →が押されたか
    if( pState->Right )
    {
        direction_ = 2;
        position_.x += 4.0F;
    }

    // ←が押されたか
    if( pState->Left )
    {
        direction_ = 3;
        position_.x -= 4.0F;
    }

    // どれも押されていない
    if( !(pState->Down || pState->Up || pState->Right || pState->Left) )
    {
        animation_no_ = 0;
    }
    else
    {
        animation();
    }

    // 壁をつなぐ

    if( position_.x < -64.0F )
    {
        position_.x = 1280.0F;
    }
    if( position_.x > 1280.0F )
    {
        position_.x = -64.0F;
    }
    if( position_.y < -96.0F )
    {
        position_.y = 720.0F;
    }
    if( position_.y > 720.0F )
    {
        position_.y = -96.0F;
    }
}

// 描画
void Player::draw()
{
    // 描画範囲の設定
    rect.top    = direction_ * kPlayersizeY; /*+ hakase*/;
    rect.left   = animation_no_ * kPlayersizeX + haruka;
    rect.right  = rect.left + kPlayersizeX;
    rect.bottom = rect.top + kPlayersizeY;

    Vector2 scale;
    Vector2 origin;
    
    /*
    Sprite::draw(
        texture_,           // テクスチャ
        position_,          // 座標
        &rect,              // 描画範囲
        0.0F,               // カラー
        scale,
        origin,             // アンカーポイント（原点）
        SpriteEffects::SpriteEffects_None, // エフェクト
        0.0F                // 深度値
    );
    */

    // 描画
    Sprite::draw( texture_, position_, &rect );     // ヘッダーにデフォルト引数を入れたため省略
}

// 破棄
void Player::destroy()
{
    texture_->Release();
}
