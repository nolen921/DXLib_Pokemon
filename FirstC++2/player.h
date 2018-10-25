#pragma once
#include<d3d11.h>
#include<SpriteBatch.h>
#include<WICTextureLoader.h>
#include<SimpleMath.h>
#include<Keyboard.h>

using namespace DirectX;
using namespace SimpleMath;

// クラス宣言
class Player
{
private:
    ID3D11ShaderResourceView* texture_; // テクスチャ
    Vector2 position_;                  // 座標
    float speed_;                       // 移動速度
    RECT rect;                          // 描画範囲
    void animation();
    int animation_no_;                  // テクスチャの番号
    int animation_counter_;             // アニメーション用ループカウント
    int direction_;                     // キャラの向き

public:
    Player();                           // コンストラクタ
    ~Player();                          // デストラクタ

    // 初期化
    bool init( const wchar_t* FileName );

    // 更新処理
    void update(const Keyboard::State* pState);

    // 描画
    void draw();

    void destroy();
};