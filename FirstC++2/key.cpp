#include "key.h"

// 実体の作成
Keyboard* Key::key_;
Keyboard::State Key::state_;

bool Key::init()
{
    // キーボードのメモリ確保
    key_ = new Keyboard;

    // メモリ確保チェック
    if( !key_ )
    {
        // エラー
        return false;
    }

    return true;
}

void Key::update()
{
    // 入力情報を更新
    state_ = key_->GetState();
}