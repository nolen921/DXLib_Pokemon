#pragma once

#include<Windows.h>
#include<Keyboard.h>

using namespace DirectX;

// Class
class Key
{
private:
    static Keyboard key_;     // キーボードクラス
    static Keyboard::State state_;   // キーボード入力の情報
public:
    static void update();  // 更新処理
    static const Keyboard::State& getState() { return state_; } // 入力情報を返す
};