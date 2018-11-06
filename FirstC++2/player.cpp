#include"player.h"
#include"texture.h"
#include"sprite.h"
#include"field.h"

/* pokemon_char�̑傫�� */
int kPlayertop = 0L;
int kPlayersizeX = 64L;
int kPlayersizeY = 96L;

const int haruka = 256;
const int hakase = 384;

int Player::masu_position_x_;
int Player::masu_position_y_;

// �R���X�g���N�^
Player::Player()
{
    // �����o�ϐ�������
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
    dash_ = false;
    masu_position_x_ = 10;
    masu_position_y_ = 6;

    jump_down_flag_ = false;               // �W�����v�t���O��
    jump_right_flag_ = false;              // �W�����v�t���O�E
    jump_left_flag_ = false;               // �W�����v�t���O��

    collision_ = false;
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
    if( animation_counter_ >= 12 )
    {
        animation_counter_ = 0;
        animation_no_++;
        if( animation_no_ > 3 )
            animation_no_ = 0;
    }
    animation_counter_++;
    if( dash_ || jump_down_flag_ || jump_left_flag_ || jump_right_flag_ )
        animation_counter_++;
}

// �X�V����
void Player::update( const Keyboard::State* pState )
{
    // ��shift�������ꂽ��
    if( move_ == false && !(jump_down_flag_ || jump_left_flag_ || jump_right_flag_) && (pState->Down || pState->Up || pState->Right || pState->Left) && pState->LeftShift )
    {
        dash_ = true;   
    }

    // ���������ꂽ��
    if( move_ == false && !(jump_down_flag_ || jump_left_flag_ || jump_right_flag_) && pState->Down )
    {
        key_counter_++;     // ������

        direction_ = 0;

        if( key_counter_ >= 8 )
        {
            if( Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ + Field::getMapWidth() ) >= 128 && Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ + Field::getMapWidth() ) <= 130 )
            {
                masu_position_y_+= 2;
                jump_down_flag_ = true;
            }
            else if(( Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ + Field::getMapWidth() ) <= 63 || Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ + Field::getMapWidth() ) >= 230 ) && ( Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ + Field::getMapWidth() + 10000 ) <= 63 || Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ + Field::getMapWidth() + 10000 ) >= 230 ) )
            {
                masu_position_y_++;
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
    else if( move_ == false && !(jump_down_flag_ || jump_left_flag_ || jump_right_flag_) && pState->Up )
    {
        key_counter_++;     // ������

        direction_ = 1;

        if( key_counter_ >= 8 )
        {
            if(( Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ - Field::getMapWidth()) <= 63 || Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ - Field::getMapWidth() ) >= 230 ) && (Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ - Field::getMapWidth() + 10000 ) <= 63 || Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ - Field::getMapWidth() + 10000 ) >= 230) )
            {
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
    else if( move_ == false && !(jump_down_flag_ || jump_left_flag_ || jump_right_flag_) && pState->Right )
    {
        key_counter_++;     // ������

        direction_ = 2;

        if( Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ + 1 ) == 100 || Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ + 1 ) == 116 )
        {
            masu_position_x_ += 2;
            jump_right_flag_ = true;
        }
        else if( key_counter_ >= 8 )
        {
            if(( Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ + 1 ) <= 63 || Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ + 1 ) >= 230 ) && (Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ + 1 + 10000 ) <= 63 || Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ + 1 + 10000 ) >= 230) )
            {
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
    else if( move_ == false && !(jump_down_flag_ || jump_left_flag_ || jump_right_flag_) && pState->Left )
    {
        key_counter_++;     // ������

        direction_ = 3;

        if( key_counter_ >= 8 )
        {
            if( Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ -1 ) == 99 || Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ -1 ) == 115 )
            {
                masu_position_x_ -= 2;
                jump_left_flag_ = true;
            }
            else if(( Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ - 1) <= 63 || Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ - 1 ) >= 230 ) && (Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ - 1 + 10000 ) <= 63 || Field::getPartsId( masu_position_y_ * Field::getMapWidth() + masu_position_x_ - 1 + 10000 ) >= 230) )
            {
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
    if(move_ == false && !(jump_down_flag_ || jump_left_flag_ || jump_right_flag_) && !(pState->Down || pState->Up || pState->Right || pState->Left ) )
    {
        dash_ = false;
        animation_no_ = 0;
        key_counter_ = 0;
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
                if( (!pState->LeftShift) || !(pState->Down || pState->Up || pState->Right || pState->Left) )
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

    if( jump_down_flag_ )
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
            jump_down_flag_ = false;
        }
    }
    else if( jump_right_flag_ )
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
            jump_right_flag_ = false;
        }
    }
    else if( jump_left_flag_ )
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
            jump_left_flag_ = false;
        }
    }


    // �ǂ��Ȃ�
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

// �`��
void Player::draw()
{
    // �`��͈͂̐ݒ�
    rect.top = direction_ * kPlayersizeY + (dash_ ? 384L : 0L);
    rect.left   = animation_no_ * kPlayersizeX + haruka;
    rect.right  = rect.left + kPlayersizeX;
    rect.bottom = rect.top + kPlayersizeY;

    Vector2 scale;
    Vector2 origin;
    
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
    Sprite::draw( texture_, position_, &rect );     // �w�b�_�[�Ƀf�t�H���g��������ꂽ���ߏȗ�

    if( jump_down_flag_ || jump_right_flag_ || jump_left_flag_ )
    {
        rect.top = 992L;
        rect.left = 0L;
        rect.right = rect.left + 64L;
        rect.bottom = rect.top + 32L;

        Sprite::draw( texture_, Vector2( position_.x, 428.0F ) , &rect );
    }
}

// �j��
void Player::destroy()
{
    texture_->Release();
}
