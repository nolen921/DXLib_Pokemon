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

/* pokemon_char�̑傫�� */
int kPlayertop = 0L;
int kPlayersizeX = 64L;
int kPlayersizeY = 96L;

const int haruka = 256;
const int hakase = 384;

// ���̂̍쐬
Player Player::player_;

int Player::masu_position_x_;
int Player::masu_position_y_;
bool Player::collision_;

// �R���X�g���N�^
Player::Player()
{
    // �����o�ϐ�������
    // position_.x = static_cast<float>(rand() % 1280);
    // position_.y = static_cast<float>(rand() % 720);
    // speed_ = static_cast<float>(rand() % 10) + 2.0F;
    position_.x = 640.0F;
    position_.y = 352.0F;
    scale_ = 1.0F;              // �X�P�[���l
    flip_ = SpriteEffects_None; // ���]
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

    jump_switch_ = 0;       // �W�����v�X�C�b�`

    collision_ = false;
    enterPokecen_ = false;

    //
    texture_ = NULL;
}

// �f�X�g���N�^
Player::~Player()
{

}

bool Player::init( const wchar_t* FileName )
{
    // load��static�ɂ���Ƃ���Ȃ��@���@Texture tex;
    texture_ = Texture::load( FileName );

    if( texture_ == NULL )
    {
        // �G���[
        return false;
    }

    /*
    Texture::num_ = 100;    // static�����o�ϐ������̂�������̂ł����ł��g����

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

// �X�V����
void Player::update()
{
    // �L�[�{�[�h���͂��擾
    const Keyboard::State pState = Key::getState();
    // �R���g���[�����͂��擾
    const GamePad::State pad = Pad::getstate();
    // �}�E�X���͂��擾
    const Mouse::State ms = MyMouse::getState();

    // �}�E�X���W�Ƀe�N�X�`�����ړ�
    // position_.x = static_cast<float>(ms.x);
    // position_.y = static_cast<float>(ms.y);

    // ���N���b�N���Ă���Ԃ̓e�N�X�`���𔽓]������
    if( ms.leftButton ) 
        flip_ = SpriteEffects_FlipHorizontally;

    // �z�C�[���ŃT�C�Y�ύX
    // �z�C�[���͈ȉ��̂悤�ȋ������s���܂��B
    // �}�E�X�z�C�[������]�����Ƃ��ɃJ�`�b�Ɩ����񐔂ɌW�����|�������l���񍐂���܂��BMicrosoftWindows�v���b�g�t�H�[���̌W����120�ł��B(Microsoft�̃��t�@�����X�����p)
    scale_ = 1.0F + static_cast<float>(ms.scrollWheelValue / 120);

    // mouse.ResetScrollWheelValue();

    // ��shift�������ꂽ��
    if( move_ == false && enterPokecen_ == false && jump_switch_ == 0 && (pState.Down || pState.Up || pState.Right || pState.Left || pad.dpad.down || pad.dpad.up || pad.dpad.left || pad.dpad.right ) && ( pState.LeftShift || pad.buttons.a ) )
    {
        dash_ = true;
    }

    // ���������ꂽ��
    if( move_ == false && enterPokecen_ == false && jump_switch_ == 0 && ( pState.Down || pad.dpad.down ) )
    {
        key_counter_++;     // ������

        direction_ = 0;

        if( key_counter_ >= 8 )
        {
            Collision::collision( direction_ );
        }
    }
    // ���������ꂽ��
    else if( move_ == false && enterPokecen_ == false && jump_switch_ == 0 && ( pState.Up || pad.dpad.up ) )
    {
        key_counter_++;     // ������

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
    // ���������ꂽ��
    else if( move_ == false && enterPokecen_ == false && jump_switch_ == 0 && ( pState.Right || pad.dpad.right ) )
    {
        key_counter_++;     // ������

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
    // ���������ꂽ��
    else if( move_ == false && enterPokecen_ == false && jump_switch_ == 0 && ( pState.Left || pad.dpad.left ) )
    {
        key_counter_++;     // ������

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
    
    // �ǂ��������Ă��Ȃ�
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

        // ���������ꂽ��
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
        // ���������ꂽ��
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
        // ���������ꂽ��
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
        // ���������ꂽ��
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


    // �|�P�����Z���^�[�ɓ��鏈��
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

// �`��
void Player::draw()
{
    // �`��͈͂̐ݒ�
    rect.top = direction_ * kPlayersizeY + (dash_ ? 384L : 0L);
    rect.left   = player_.animation_no_ * kPlayersizeX + haruka;
    rect.right  = rect.left + kPlayersizeX;
    rect.bottom = rect.top + kPlayersizeY;
    
    /*
    Sprite::draw(
        texture_,           // �e�N�X�`��
        position_,          // ���W
        &rect,              // �`��͈�
        0.0F,               // �J���[
        scale,
        origin,             // �A���J�[�|�C���g�i���_�j
        SpriteEffects::SpriteEffects_None, // �G�t�F�N�g
        0.0F                // �[�x�l
    );
    */

    // �`��
    Sprite::draw( texture_, position_, &rect, Colors::White, 0.0F, Vector2::Zero, scale_, flip_ );

    if( jump_switch_ )
    {
        rect.top = 992L;
        rect.left = 0L;
        rect.right = rect.left + 64L;
        rect.bottom = rect.top + 32L;

        Sprite::draw( texture_, Vector2( position_.x, 428.0F ) , &rect );
    }

    // ���W��`��
    char str[ 256 ];
    sprintf( str, "position.x = %.1f\nposition.y = %.1f", position_.x, position_.y );

    // ���C�h�����ɕϊ�
    wchar_t wstr[ 256 ];
    mbstowcs( wstr, str, 256 );
    //Font::draw( wstr, Vector2::Zero );
}

// �j��
void Player::destroy()
{
    SAFE_RELEASE( texture_ );
}
