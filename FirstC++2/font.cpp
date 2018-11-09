#include "font.h"

// ���̂̐錾
SpriteFont* Font::font_;

// ������

bool Font::init()
{
    // �X�v���C�g�t�H���g�̃��������m��
    font_ = new SpriteFont( Direct3D::getDevice(), L"HGPsouei_presens_EB.spritefont" );

    // �������m�ۃ`�F�b�N
    if( !font_ )
    {
        // �G���[
        Error::showDialog( "�X�v���C�g�t�H���g�̃������m�ۂɎ��s���܂����B" );
        return false;
    }

    return true;
}

void Font::destroy()
{
    delete font_;
}

// �`��
void Font::draw( const wchar_t* String, const Vector2& Position )
{
    font_->DrawString( Sprite::getSprite(), String, Position,Colors::Red );
}