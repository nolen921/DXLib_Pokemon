#include"player.h"
#include"texture.h"
#include"sprite.h"
#include"field.h"

/* pokemon_charの大きさ */
int kPlayertop = 0L;
int kPlayersizeX = 64L;
int kPlayersizeY = 96L;

const int haruka = 256;
const int hakase = 384;

int Player::masu_position_x_;
int Player::masu_position_y_;

// コンストラクタ
Player::Player()
{
    // メンバ変数初期化
    // position_.x = static_cast<float>(rand() % 1280);
    // position_.y = static_cast<float>(rand() % 720);
    // speed_ = static_cast<float>(rand() % 10) + 2.0F;
    position_.x = 640.0F;
    position_.y = 352.0F;
    speed_ = 4.0F;
    animation_no_ = 0;
    animation_counter_ = 0;
    rect.top = 0L;
    rect.left = 0L;
    rect.right = 64L;
    rect.bottom = 96L;
    direction_ = 0;
    key_counter_ = 0;
    move_ = false;
    move_counter_ = 0;
    masu_position_x_ = 10;
    masu_position_y_ = 6;
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
    if( move_ == false && pState->Down)
    {
        key_counter_++;     // 長押し

        direction_ = 0;

        if(key_counter_ >= 8 )
        {
            if(( Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ + Field::getMapWidth() ) <= 63 || Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ + Field::getMapWidth() ) >= 230 ) && ( Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ + Field::getMapWidth() + 10000 ) <= 63 || Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ + Field::getMapWidth() + 10000 ) >= 230 ) )
            {
                masu_position_y_++;
                move_ = true;
            }
        }
    }
    // ↑が押されたか
    else if( move_ == false && pState->Up )
    {
        key_counter_++;     // 長押し

        direction_ = 1;

        if( key_counter_ >= 8 )
        {
            if(( Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ - Field::getMapWidth()) <= 63 || Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ - Field::getMapWidth() ) >= 230 ) && (Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ - Field::getMapWidth() + 10000 ) <= 63 || Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ - Field::getMapWidth() + 10000 ) >= 230) )
            {
                masu_position_y_--;
                move_ = true;
            }
        }
    }
    // →が押されたか
    else if( move_ == false && pState->Right )
    {
        key_counter_++;     // 長押し

        direction_ = 2;

        if( key_counter_ >= 8 )
        {
            if(( Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ + 1 ) <= 63 || Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ + 1 ) >= 230 ) && (Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ + 1 + 10000 ) <= 63 || Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ + 1 + 10000 ) >= 230) )
            {
                masu_position_x_++;
                move_ = true;
            }
        }
    }
    // ←が押されたか
    else if( move_ == false && pState->Left )
    {
        key_counter_++;     // 長押し

        direction_ = 3;

        if( key_counter_ >= 8 )
        {
            if(( Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ - 1) <= 63 || Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ - 1 ) >= 230 ) && (Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ - 1 + 10000 ) <= 63 || Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ - 1 + 10000 ) >= 230) )
            {
                masu_position_x_--;
                move_ = true;
            }
        }
    }
    
    // どれも押されていない
    if(move_ == false && !(pState->Down || pState->Up || pState->Right || pState->Left) )
    {
        animation_no_ = 0;
        key_counter_ = 0;
    }

    if( move_ )
    {
        animation();

        // ↓が押されたか
        switch( direction_ )
        {
        case 0:
            Field::move_y( 4.0F );
            break;
        // ↑が押されたか
        case 1:
            Field::move_y( -4.0F );
            break;
        // →が押されたか
        case 2:
            Field::move_x( 4.0F );
            break;
        // ←が押されたか
        case 3:
            Field::move_x( -4.0F );
            break;
        }

        move_counter_++;

        if( move_counter_ >= 16 )
        {
            move_counter_ = 0;
            move_ = false;
        }
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
