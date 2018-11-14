#pragma once
#include<d3d11.h>
#include<SpriteBatch.h>
#include<WICTextureLoader.h>
#include<SimpleMath.h>
#include<Keyboard.h>
#include"release.h"

using namespace DirectX;
using namespace SimpleMath;

// クラス宣言
class Player
{
private:
    static Player player_;
    ID3D11ShaderResourceView* texture_; // テクスチャ
    Vector2 position_;                  // 座標
    float speed_;                       // 移動速度
    RECT rect;                          // 描画範囲
    float scale_;                       // スケール値
    SpriteEffects flip_;                // 反転
    int animation_no_;                  // テクスチャの番号
    int animation_counter_;             // アニメーション用ループカウント
    int direction_;                     // キャラの向き
    int key_counter_;                   // 入力用ループカウンター
    bool move_;                         // 移動中フラグ0/1
    int move_counter_;                  // 移動用ループカウンター
    bool dash_;                         // ダッシュフラグ0/1
    int jump_switch_;                   // ジャンプスイッチ(0～3)
    static int masu_position_x_, masu_position_y_;         // マス単位の座標
    static bool collision_;             // 衝突している
    bool enterPokecen_;                 // ポケモンセンターに入る

public:
    Player();                           // コンストラクタ
    ~Player();                          // デストラクタ

    // 初期化
    bool init( const wchar_t* FileName );

    // 更新処理
    void update();

    // アニメーション
    static void animation();

    // マス単位のプレイヤーX座標を取得
    static int getMasuPositionX() { return masu_position_x_; }
    // マス単位のプレイヤーY座標を取得
    static int getMasuPositionY() { return masu_position_y_; }

    // マス単位のプレイヤーX座標を設定
    static void setMasuPositionX(int n) { masu_position_x_ = n; }
    // マス単位のプレイヤーY座標を設定
    static void setMasuPositionY(int n) { masu_position_y_ = n; }

    // moveを設定
    static void setMove( bool a );

    // jump_switchを設定
    static void setJumpSwitch( int n );

    // collisionを設定
    static void setCollision( bool a ) { collision_ = a; }

    // dash_を返す関数
    bool getDash() { return dash_; }

    // 描画
    void draw();

    void destroy();
};