#include"player.h"
#include"texture.h"
#include"sprite.h"
#include"field.h"
#include "pad.h"
#include "font.h"
#include "key.h"
#include "mouse.h"
#include "adx.h"
#include "collision.h"

/* pokemon_charの大きさ */
int kPlayertop = 0L;
int kPlayersizeX = 64L;
int kPlayersizeY = 96L;

const int haruka = 256;
const int hakase = 384;

// 実体の作成
Player Player::player_;

int Player::masu_position_x_;
int Player::masu_position_y_;
bool Player::collision_;

// コンストラクタ
Player::Player()
{
    // メンバ変数初期化
    // position_.x = static_cast<float>(rand() % 1280);
    // position_.y = static_cast<float>(rand() % 720);
    // speed_ = static_cast<float>(rand() % 10) + 2.0F;
    position_.x = 640.0F;
    position_.y = 352.0F;
    scale_ = 1.0F;              // スケール値
    flip_ = SpriteEffects_None; // 反転
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
    dash_ = false;
    masu_position_x_ = 10;
    masu_position_y_ = 6;

    jump_switch_ = 0;       // ジャンプスイッチ

    collision_ = false;
    enterPokecen_ = false;

    //
    texture_ = NULL;
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
    if( player_.animation_counter_ >= 12 )
    {
        player_.animation_counter_ = 0;
        player_.animation_no_++;
        if( player_.animation_no_ > 3 )
            player_.animation_no_ = 0;
    }
    player_.animation_counter_++;
}

// 更新処理
void Player::update()
{
    // キーボード入力を取得
    const Keyboard::State pState = Key::getState();
    // コントローラ入力を取得
    const GamePad::State pad = Pad::getstate();
    // マウス入力を取得
    const Mouse::State ms = MyMouse::getState();

    // マウス座標にテクスチャを移動
    // position_.x = static_cast<float>(ms.x);
    // position_.y = static_cast<float>(ms.y);

    // 左クリックしている間はテクスチャを反転させる
    if( ms.leftButton ) 
        flip_ = SpriteEffects_FlipHorizontally;

    // ホイールでサイズ変更
    // ホイールは以下のような挙動を行います。
    // マウスホイールを回転したときにカチッと鳴った回数に係数を掛けた数値が報告されます。MicrosoftWindowsプラットフォームの係数は120です。(Microsoftのリファレンスより引用)
    scale_ = 1.0F + static_cast<float>(ms.scrollWheelValue / 120);

    // mouse.ResetScrollWheelValue();

    // 左shiftが押されたか
    if( move_ == false && enterPokecen_ == false && jump_switch_ == 0 && (pState.Down || pState.Up || pState.Right || pState.Left || pad.dpad.down || pad.dpad.up || pad.dpad.left || pad.dpad.right ) && ( pState.LeftShift || pad.buttons.a ) )
    {
        dash_ = true;
    }

    // ↓が押されたか
    if( move_ == false && enterPokecen_ == false && jump_switch_ == 0 && ( pState.Down || pad.dpad.down ) )
    {
        key_counter_++;     // 長押し

        direction_ = 0;

        if( key_counter_ >= 8 )
        {
            Collision::collision( direction_ );
        }
    }
    // ↑が押されたか
    else if( move_ == false && enterPokecen_ == false && jump_switch_ == 0 && ( pState.Up || pad.dpad.up ) )
    {
        key_counter_++;     // 長押し

        direction_ = 1;

        if( key_counter_ >= 8 )
        {
            if( Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ - Field::getMapWidth() ) == 153 )
            {
                collision_ = false;
                enterPokecen_ = true;
                dash_ = false;
            }
            else if(( Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ - Field::getMapWidth()) <= 63 || Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ - Field::getMapWidth() ) >= 230 ) && (Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ - Field::getMapWidth() + 10000 ) <= 63 || Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ - Field::getMapWidth() + 10000 ) >= 230) )
            {
                collision_ = false;
                masu_position_y_--;
                move_ = true;
            }
            else
            {
                collision_ = true;
                animation();
            }
        }
    }
    // →が押されたか
    else if( move_ == false && enterPokecen_ == false && jump_switch_ == 0 && ( pState.Right || pad.dpad.right ) )
    {
        key_counter_++;     // 長押し

        direction_ = 2;

        if( key_counter_ >= 8 )
        {
            if( Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ + 1 ) == 100 || Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ + 1 ) == 116 )
            {
                collision_ = false;
                masu_position_x_ += 2;
                jump_switch_ = 2;
            }
            else if(( Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ + 1 ) <= 63 || Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ + 1 ) >= 230 ) && (Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ + 1 + 10000 ) <= 63 || Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ + 1 + 10000 ) >= 230) )
            {
                collision_ = false;
                masu_position_x_++;
                move_ = true;
            }
            else
            {
                collision_ = true;
                animation();
            }
        }
    }
    // ←が押されたか
    else if( move_ == false && enterPokecen_ == false && jump_switch_ == 0 && ( pState.Left || pad.dpad.left ) )
    {
        key_counter_++;     // 長押し

        direction_ = 3;

        if( key_counter_ >= 8 )
        {
            if( Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ -1 ) == 99 || Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ -1 ) == 115 )
            {
                collision_ = false;
                masu_position_x_ -= 2;
                jump_switch_ = 3;
            }
            else if(( Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ - 1) <= 63 || Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ - 1 ) >= 230 ) && (Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ - 1 + 10000 ) <= 63 || Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ - 1 + 10000 ) >= 230) )
            {
                collision_ = false;
                masu_position_x_--;
                move_ = true;
            }
            else
            {
                collision_ = true;
                animation();
            }
        }
    }
    
    // どれも押されていない
    if(move_ == false && enterPokecen_ == false && jump_switch_ == 0 && !(pState.Down || pState.Up || pState.Right || pState.Left ) && !(pad.dpad.down || pad.dpad.up || pad.dpad.left || pad.dpad.right ) )
    {
        dash_ = false;
        animation_no_ = 0;
        key_counter_ = 0;
    }

    if( collision_ == true )
    {
        dash_ = false;
    }

    if( move_ )
    {
        animation();

        // ↓が押されたか
        switch( direction_ )
        {
        case 0:
            if( dash_ )
            {
                Field::move_y( 8.0F );
            }
            else
            {
                Field::move_y( 4.0F );
            }
            break;
        // ↑が押されたか
        case 1:
            if( dash_ )
            {
                Field::move_y( -8.0F );
            }
            else
            {
                Field::move_y( -4.0F );
            }
            break;
        // →が押されたか
        case 2:
            if( dash_ )
            {
                Field::move_x( 8.0F );
            }
            else
            {
                Field::move_x( 4.0F );
            }
            break;
        // ←が押されたか
        case 3:
            if( dash_ )
            {
                Field::move_x( -8.0F );
            }
            else
            {
                Field::move_x( -4.0F );
            }
            break;
        }

        move_counter_++;

        if( dash_ )
        {
            if( move_counter_ >= 8 )
            {
                move_counter_ = 0;
                move_ = false;
                if( !(pState.LeftShift || pad.buttons.a) || !(pState.Down || pState.Up || pState.Right || pState.Left || pad.dpad.down || pad.dpad.up || pad.dpad.left || pad.dpad.right ) )
                    dash_ = false;
            }
        }
        else
        {
            if( move_counter_ >= 16 )
            {
                move_counter_ = 0;
                move_ = false;
            }
        }
    }


    if( dash_ || jump_switch_ )
        animation_counter_++;

    if( jump_switch_ == 1 )
    {
        dash_ = false;

        animation();

        Field::move_y( 4.0F );

        move_counter_++;

        if( move_counter_ <= 12 )
        {
            position_.y -= 5;
        }
        else
        {
            position_.y += 3;
        }

        if( move_counter_ >= 32 )
        {
            move_counter_ = 0;
            jump_switch_ = 0;
        }
    }
    else if( jump_switch_ == 2 )
    {
        dash_ = false;

        animation();

        Field::move_x( 4.0F );

        move_counter_++;

        if( move_counter_ <= 12 )
        {
            position_.y -= 5;
        }
        else
        {
            position_.y += 3;
        }

        if( move_counter_ >= 32 )
        {
            move_counter_ = 0;
            jump_switch_ = 0;
        }
    }
    else if( jump_switch_ == 3 )
    {
        dash_ = false;

        animation();

        Field::move_x( -4.0F );

        move_counter_++;

        if( move_counter_ <= 12 )
        {
            position_.y -= 5;
        }
        else
        {
            position_.y += 3;
        }

        if( move_counter_ >= 32 )
        {
            move_counter_ = 0;
            jump_switch_ = 0;
        }
    }


    // ポケモンセンターに入る処理
    if( enterPokecen_ )
    {
        move_counter_++;
        
        if( move_counter_ <= 32 )
        {
            if( move_counter_ % 16 == 0 )
            {
                Field::setPartsTrim( Field::getIndex() - Field::getMapWidth(), 64, 64, 0, 0 );
                Field::setPartsTrim( Field::getIndex() - (Field::getMapWidth() * 2), 64, 64, 0, 0 );
            }
        }
        else if( move_counter_ <= 48 )
        {
            animation();
            Field::move_y( -4.0F );
        }
        else
        {
            Field::set_x( 80 * 64.0F );
            Field::set_y( 5 * 64.0F );


            Field::setPartsTrim( masu_position_y_ * Field::getMapWidth() + masu_position_x_ - Field::getMapWidth(), -128, -128, 0, 0 );
            Field::setPartsTrim( masu_position_y_ * Field::getMapWidth() + masu_position_x_ - (Field::getMapWidth() * 2), -128, -128, 0, 0 );

            masu_position_x_ = 90;
            masu_position_y_ = 11;
            enterPokecen_ = false;
            move_counter_ = 0;
        }
    }

}

void Player::setMove( bool a )
{
    player_.move_ = a;
}

void Player::setJumpSwitch( int n )
{
    player_.jump_switch_ = n;
}

// 描画
void Player::draw()
{
    // 描画範囲の設定
    rect.top = direction_ * kPlayersizeY + (dash_ ? 384L : 0L);
    rect.left   = player_.animation_no_ * kPlayersizeX + haruka;
    rect.right  = rect.left + kPlayersizeX;
    rect.bottom = rect.top + kPlayersizeY;
    
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
    Sprite::draw( texture_, position_, &rect, Colors::White, 0.0F, Vector2::Zero, scale_, flip_ );

    if( jump_switch_ )
    {
        rect.top = 992L;
        rect.left = 0L;
        rect.right = rect.left + 64L;
        rect.bottom = rect.top + 32L;

        Sprite::draw( texture_, Vector2( position_.x, 428.0F ) , &rect );
    }

    // 座標を描画
    char str[ 256 ];
    sprintf( str, "position.x = %.1f\nposition.y = %.1f", position_.x, position_.y );

    // ワイド文字に変換
    wchar_t wstr[ 256 ];
    mbstowcs( wstr, str, 256 );
    //Font::draw( wstr, Vector2::Zero );
}

// 破棄
void Player::destroy()
{
    SAFE_RELEASE( texture_ );
}
