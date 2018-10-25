#pragma once

#include<Windows.h>
#include<Keyboard.h>

using namespace DirectX;

// Class
class Key
{
private:
    static Keyboard* key_;     // キーボードクラス
    static Keyboard::State state_;   // キーボード入力の情報
public:
    static bool init();     // 初期化
    static void update();   // 更新
    static void destroy() { delete(key_); }  // 破棄

    // キーボード入力の取得
    static Keyboard::State* getNyuryoku() { return &state_; }
};