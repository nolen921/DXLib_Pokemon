#pragma once

#include<GamePad.h>

using namespace DirectX;

class Pad
{
private:
    static GamePad pad_;            // ゲームパッドクラス
    static GamePad::State state_;   // 入力格納構造体

public:
    static void update();   // 更新処理

    // 入力構造体を返す
    static const GamePad::State& getstate() { return state_; }

    // 振動の設定
    static void setVibration( const float Left, const float Right )
    {
        pad_.SetVibration( 0, Left, Right );
    }
};