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
    int key_counter_;                   // 入力用ループカウンター
    bool move_;                         // 移動中フラグ0/1
    int move_counter_;                  // 移動用ループカウンター
    bool dash_;                         // ダッシュフラグ0/1
    bool jump_down_flag_;               // ジャンプフラグ下
    bool jump_right_flag_;              // ジャンプフラグ右
    bool jump_left_flag_;               // ジャンプフラグ左
    static int masu_position_x_, masu_position_y_;         // マス単位の座標

public:
    Player();                           // コンストラクタ
    ~Player();                          // デストラクタ

    // 初期化
    bool init( const wchar_t* FileName );

    // 更新処理
    void update(const Keyboard::State* pState);

    // マス単位のプレイヤーX座標を取得
    static int getMasuPositionX() { return masu_position_x_; }
    // マス単位のプレイヤーY座標を取得
    static int getMasuPositionY() { return masu_position_y_; }

    // dash_を返す関数
    bool getDash() { return dash_; }

    // 描画
    void draw();

    void destroy();
};