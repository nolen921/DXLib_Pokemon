#include "title.h"
#include "texture.h"
#include "sprite.h"
#include "key.h"

// ������
bool Title::init()
{
    // �e�N�X�`���̓ǂݍ���
    if( !(texture_ = Texture::load( L"pokemon_rse2.png" )) )
    {
        // �G���[
        return false;
    }

    return true;
}

// �X�V
bool Title::update()
{
    const Keyboard::State key = Key::getState();

    // �X�y�[�X�L�[�������ꂽ��^�C�g����ʏI��
    if( key.Space )
    {
        return false;
    }

    return true;
}

// �`��
void Title::draw()
{
    Sprite::draw( texture_, Vector2::Zero );
}

// �j��
void Title::destroy()
{
    // �e�N�X�`���̉��
    SAFE_RELEASE( texture_ );
}