#pragma once

#include"direct3d.h"
#include"sprite.h"

// 構造体
struct Parts
{
    Vector2 position;   // 座標
    RECT trim;          // 描画範囲
    int id;             // パーツ番号
    int layer;          // レイヤー番号

    // コンストラクタ
    Parts()
    {
        position = Vector2( 0.0F, 0.0F );
        trim = RECT{ 0 };
        id = 0;
        layer = 0;
    }
};

// クラス
class Field
{
private:
    ID3D11ShaderResourceView* texture_;         // テクスチャ
    static int width_, height_;                 // マップ横幅縦幅
    static int LayerCount_;                     // レイヤー数
    static Parts* parts_;                       // パーツ構造体ポインタ
    static float offset_x_, offset_y_;          // スクロール用
    int index_;                                 // 足元のパーツ番号

public:
    Field();        // コンストラクタ
    ~Field() {};    // デストラクタ
    bool init();    // 初期化
    static void move_x( const float x );    // 更新
    static void move_y( const float y );    // 更新
    static int getPartsId( int i );         // パーツ番号を取得
    static int getLayer( int i );           // レイヤー番号を取得
    static int getMapWidth();               // マップ横幅を取得
    static int getMapHeight();              // マップ縦幅を取得
    int getIndex();                         // インデックスを取得
    float getOffsetX() { return offset_x_; }  // オフセットxを取得
    float getOffsetY() { return offset_y_; }  // オフセットyを取得
    void draw(int n);                       // 描画
    void destroy();                         // 破棄
};