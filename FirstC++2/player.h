#pragma once
#include<d3d11.h>
#include<SpriteBatch.h>
#include<WICTextureLoader.h>
#include<SimpleMath.h>

using namespace DirectX;
using namespace SimpleMath;

// クラス宣言
class Player
{
private:
    ID3D11ShaderResourceView* texture_; // テクスチャ
    Vector2 position_;                  // 座標
    float speed_;                       // 移動速度

public:
    Player();                           // コンストラクタ
    ~Player();                          // デストラクタ

    // 初期化
    bool init( const wchar_t* FileName, ID3D11Device* Device, ID3D11DeviceContext* Context );

    // 更新処理
    void update();

    // 描画
    void draw( SpriteBatch* Sprite );

    void destroy();
};