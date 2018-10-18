#include"player.h"
#include"texture.h"

// �R���X�g���N�^
Player::Player()
{
    // �����o�ϐ�������
    position_.x = static_cast<float>(rand() % 1280);
    position_.y = static_cast<float>(rand() % 720);
    speed_ = static_cast<float>(rand() % 10) + 2.0F;
}

// �f�X�g���N�^
Player::~Player()
{

}

bool Player::init( const wchar_t* FileName, ID3D11Device* Device, ID3D11DeviceContext* Context )
{
    // 
    // load��static�ɂ���Ƃ���Ȃ��@���@Texture tex;
    texture_ = Texture::load( FileName, Device, Context );

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

    // �����o�ϐ�������
    position_.x = static_cast<float>(rand() % 1280);
    position_.y = static_cast<float>(rand() % 720);
    speed_ = static_cast<float>(rand() % 10) + 2.0F;

    return true;
}

// �X�V����
void Player::update()
{
    // �ړ�
    position_.x += speed_;

    if( position_.x > 1280.0F )
    {
        position_.x = -64.0F;
    }
}

// �`��
void Player::draw( SpriteBatch* Sprite )
{
    // �`��͈͂̐ݒ�
    RECT rect;
    rect.top = 0L;
    rect.left = 0L;
    rect.right = 64L;
    rect.bottom = 64L;

    static float rotate = 0.0F;
    rotate++;
    

    Sprite->Draw(
        texture_,           // �e�N�X�`��
        position_,          // ���W
        &rect,              // �`��͈�
        Colors::Red,        // �J���[
        rotate * XM_PI / 180.0F,               // ��]�l
        Vector2(32.0F,32.0F), // �A���J�[�|�C���g�i���_�j
        Vector2(1.0F,1.0F), // �g�k
        SpriteEffects_None, // �G�t�F�N�g
        0.0F                // �[�x�l
    );
}

// �j��
void Player::destroy()
{
    texture_->Release();
}
