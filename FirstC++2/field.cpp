#include "field.h"
#include "texture.h"
#include "sprite.h"
#include "error.h"
#include "font.h"

Parts* Field::parts_;
float Field::offset_x_;
float Field::offset_y_;
int Field::width_;
int Field::height_;
int Field::LayerCount_;
int Field::index_;

int Field::pokecen_width_;
int Field::pokecen_height_;
int Field::Pokecen_LayerCount_;

// コンストラクタ
Field::Field()
{
    texture_ = NULL;
    texture2_ = NULL;
    parts_ = NULL;
    width_ = 0;
    height_ = 0;
    offset_x_ = 0.0F;
    offset_y_ = 0.0F;
    index_ = 0;
}

// 初期化
bool Field::init()
{
    // テクスチャの読み込み
    if(!(texture_ = Texture::load( L"pokemon_rse2.png" )))
    {
        // エラー
        return false;
    }

    // ポケセンテクスチャの読み込み
    if( !(texture2_ = Texture::load( L"pokemon_center.png" )) )
    {
        // エラー
        return false;
    }

    // FMFファイルを開く
    FILE* fp = fopen( "pokemon_map.fmf", "rb" );

    if( !fp )
    {
        // エラー
        Error::showDialog( "map.fmfが開けませんでした。" );
        return false;
    }

    // 先頭8Byteをスキップ
    fseek( fp, 8L, SEEK_SET );

    // マップの横幅と縦幅を取得
    fread( &width_, sizeof( int ), 1, fp );
    fread( &height_, sizeof( int ), 1, fp );

    // 先頭18Byteをスキップ
    fseek( fp, 18L, SEEK_SET );

    // レイヤー数を取得
    fread( &LayerCount_, sizeof( char ), 1, fp );

    // Parts構造体のメモリを確保
    parts_ = new Parts[ width_ * height_ * LayerCount_ ];

    // NULLチェック
    if( !parts_ )
    {
        // エラー
        Error::showDialog( "パーツ構造体のメモリ確保に失敗しました。" );
        return false;
    }

    // FMFヘッダー部分をスキップ
    fseek( fp, 20L, SEEK_SET );

    // 全パーツデータを格納
    for( int i = 0; i < LayerCount_; i++ )
    {
        for( int j = width_ * height_ * i; j < width_ * height_* (i+1); j++ )
        {
            // 番号の取得
            fread( &parts_[ j ].id, sizeof( char ), 1, fp );

            // 描画範囲の設定
            parts_[ j ].trim.left = parts_[ j ].id % 16 * 64L;
            parts_[ j ].trim.top = parts_[ j ].id / 16 * 64L;
            parts_[ j ].trim.right = parts_[ j ].trim.left + 64L;
            parts_[ j ].trim.bottom = parts_[ j ].trim.top + 64L;

            // 座標設定
            if( i <= 2 )
            {
                parts_[ j ].position.x = static_cast<float>(64.0F * (j % width_));
                parts_[ j ].position.y = static_cast<float>(64.0F * ((j % (width_ * height_)) / width_));
            }
            else
            {
                parts_[ j ].position.x = static_cast<float>(64.0F * (j % width_));
                parts_[ j ].position.y = static_cast<float>(64.0F * ((j % (width_ * height_)) / width_));
            }
        }
    }

    // ファイルを閉じる
    fclose( fp );

    return true;
}

// 更新
void Field::move_x( const float x )
{
    offset_x_ += x;
}

void Field::move_y( const float y )
{
    offset_y_ += y;
}

// 値を指定して更新
void Field::set_x( const float x )
{
    offset_x_ = x;
}

void Field::set_y( const float y )
{
    offset_y_ = y;
}

// パーツ番号を取得
int Field::getPartsId(int i)
{
    return parts_[ i ].id;
}

// パーツの描画範囲を設定
void Field::setPartsTrim( int i, int l, int r, int t, int b )
{
    parts_[ i ].trim.left += l;
    parts_[ i ].trim.right += r;
    parts_[ i ].trim.top += t;
    parts_[ i ].trim.bottom += b;
}

// レイヤー番号を取得
int Field::getLayer()
{
    return LayerCount_;
}

// マップ横幅を取得
int Field::getMapWidth() 
{
    return width_;
}

// マップ縦幅を取得
int Field::getMapHeight()
{
    return height_;
}

int Field::getIndex()
{
    int x = static_cast<int>(offset_x_ / 64 + 10);
    int y = static_cast<int>(offset_y_ / 64 + 6);
    index_ = (y*width_) + x;

    return index_;
}

// 描画
void Field::draw( int layer, bool drawID )
{
    
    for( int i = width_ * height_ * layer; i < width_ * height_ * (layer + 1); i++ )
    {

        getIndex();
        XMVECTORF32 color = Colors::White;
        //if( i == index_ /*((offset_y_ / 64 + 6)* width_) + (offset_x_ / 64 + 10)*/ )
            //color = Colors::Red;

        if( i % width_ <= Player::getMasuPositionX() - 11 || i % width_ >= Player::getMasuPositionX() + 10 )
        {
            continue;
        }
        if( i % (width_ * height_) / width_ <= Player::getMasuPositionY() - 7 || i % (width_ * height_) / width_ >= Player::getMasuPositionY() + 5 )
        {
            continue;
        }

        if( drawID )
        {
            // 座標を描画
            char str[ 256 ];
            sprintf( str, "%d", getPartsId( i ) );

            
            // ワイド文字に変換
            wchar_t wstr[ 256 ];
            mbstowcs( wstr, str, 256 );
            Font::draw( wstr, Vector2( parts_[ i ].position.x - offset_x_, parts_[ i ].position.y - offset_y_ ) );
            
        }
        else
        {
            if( layer != 3 )
            {

                Sprite::draw( texture_, Vector2( parts_[ i ].position.x - offset_x_, parts_[ i ].position.y - offset_y_ ), &parts_[ i ].trim, color );
            }
            else
            {
                Sprite::draw( texture2_, Vector2( parts_[ i ].position.x - offset_x_, parts_[ i ].position.y - offset_y_ ), &parts_[ i ].trim, color );
            }
        }
    }
}

// 破棄
void Field::destroy()
{
    // テクスチャの解放
    SAFE_RELEASE( texture_ );

    SAFE_RELEASE( texture2_ );
    
    // メモリの開放
    SAFE_DELETE_ARRAY( parts_ );
}