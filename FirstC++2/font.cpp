#include "font.h"

// 実体の宣言
SpriteFont* Font::font_;

// 初期化

bool Font::init()
{
    // スプライトフォントのメモリを確保
    font_ = new SpriteFont( Direct3D::getDevice(), L"HGPsouei_presens_EB.spritefont" );

    // メモリ確保チェック
    if( !font_ )
    {
        // エラー
        Error::showDialog( "スプライトフォントのメモリ確保に失敗しました。" );
        return false;
    }

    return true;
}

void Font::destroy()
{
    delete font_;
}

// 描画
void Font::draw( const wchar_t* String, const Vector2& Position )
{
    font_->DrawString( Sprite::getSprite(), String, Position,Colors::Red );
}