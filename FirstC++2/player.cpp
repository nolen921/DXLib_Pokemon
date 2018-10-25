#include"player.h"
#include"texture.h"
#include"sprite.h"

/* pokemon_char�̑傫�� */
int kPlayertop = 0L;
int kPlayersizeX = 64L;
int kPlayersizeY = 96L;

const int haruka = 256;
const int hakase = 384;

// �R���X�g���N�^
Player::Player()
{
    // �����o�ϐ�������
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
}

// �X�V����
void Player::update( const Keyboard::State* pState )
{
    // ���������ꂽ��
    if( pState->Down )
    {
        direction_ = 0;
        position_.y += 4.0F;
    }

    // ���������ꂽ��
    if( pState->Up )
    {
        direction_ = 1;
        position_.y -= 4.0F;
    }

    // ���������ꂽ��
    if( pState->Right )
    {
        direction_ = 2;
        position_.x += 4.0F;
    }

    // ���������ꂽ��
    if( pState->Left )
    {
        direction_ = 3;
        position_.x -= 4.0F;
    }

    // �ǂ��������Ă��Ȃ�
    if( !(pState->Down || pState->Up || pState->Right || pState->Left) )
    {
        animation_no_ = 0;
    }
    else
    {
        animation();
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
    rect.top    = direction_ * kPlayersizeY; /*+ hakase*/;
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
}

// �j��
void Player::destroy()
{
    texture_->Release();
}
