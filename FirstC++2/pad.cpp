#include "pad.h"

// 実態の宣言
GamePad Pad::pad_;
GamePad::State Pad::state_;

// 更新処理
void Pad::update()
{
    // 入力を取得
    // 引数で何番目のコントローラの入力を取るか決める(複数つなげる場合、配列を使う)
    state_ = pad_.GetState( 0 );
}