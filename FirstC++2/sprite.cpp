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
    sprite_->Begin( SpriteSortMode_Deferred, Common::getState()->NonPremultiplied() );  /* ���̃A���t�@�錾�ɂ��A������ */
}

void Sprite::draw(
    ID3D11ShaderResourceView* Texture,  // �e�N�X�`��
    const Vector2& Position,            // ���W
    const RECT* Rect,                   // �`��͈�
    const XMVECTORF32& Color,           // �J���[
    const float Rotation,               // ��]
    const Vector2& Origin,              // �A���J�[�|�C���g
    const float Scale,                  // �g�k
    const SpriteEffects Effect,         // �G�t�F�N�g,
    const float Depth )                 // �[�x
{
    sprite_->Draw(
        Texture,                // �e�N�X�`��
        Position,               // ���W
        Rect,                   // �`��͈�
        Color,                  // �J���[
        Rotation,               // ��]�l   0.0F * XM_PI / 180.0F
        Origin,                 // �A���J�[�|�C���g�i���_�j
        Scale,                  // �g�k
        Effect,                 // �G�t�F�N�g
        Depth );                // �[�x�l
}