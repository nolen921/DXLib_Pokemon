#include "key.h"

// 実体の作成
Keyboard Key::key_;
Keyboard::State Key::state_;

void Key::update()
{
    // 入力情報を更新
    state_ = key_.GetState();
}