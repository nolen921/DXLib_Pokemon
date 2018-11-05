#include "field.h"
#include "texture.h"
#include "sprite.h"
#include "error.h"

Parts* Field::parts_;
float Field::offset_x_;
float Field::offset_y_;
int Field::width_;
int Field::height_;
int Field::LayerCount_;

// コンストラクタ
Field::Field()
{
    texture_ = NULL;
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
    if(!(texture_ = Texture::load( L"pokemon_rse.png" )))
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
            parts_[ j ].position.x = static_cast<float>(64.0F * (j % width_));
            parts_[ j ].position.y = static_cast<float>(64.0F * ((j % (width_ * height_)) / width_));
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

// パーツ番号を取得
int Field::getPartsId(int i)
{
    return parts_[ i ].id;
}

// レイヤー番号を取得
int Field::getLayer( int i )
{
    return parts_[ i ].layer;
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
void Field::draw(int n)
{
    for( int i = width_ * height_ * n; i < width_ * height_ * (n+1); i++ )
    {
        if( i % width_ <= Player::getMasuPositionX() - 10 || i % width_ >= Player::getMasuPositionX() + 9 )
        {
            continue;
        }
        if( i % (width_ * height_) / width_ <= Player::getMasuPositionY() - 6 || i % (width_ * height_) / width_ >= Player::getMasuPositionY() + 4 )
        {
            continue;
        }

        getIndex();
        XMVECTORF32 color = Colors::White;
        if( i == index_ /*((offset_y_ / 64 + 6)* width_) + (offset_x_ / 64 + 10)*/ )
            color = Colors::Red;

        Sprite::draw( texture_, Vector2( parts_[ i ].position.x - offset_x_, parts_[ i ].position.y - offset_y_ ), &parts_[ i ].trim, color );
    }
}

// 破棄
void Field::destroy()
{
    // テクスチャの解放
    texture_->Release();

    // メモリの開放
    delete[] parts_;
}