#include "mouse.h"

// 実体の作成
Mouse MyMouse::mouse_;
Mouse::State MyMouse::state_;

MyMouse::MyMouse()
{
    // Mouse::MODE_ABSOLUTE…絶対座標モード
    // Mouse::MODE_RELATIVE…相対座標モード
    mouse_.SetMode( Mouse::MODE_ABSOLUTE );
}

void MyMouse::update()
{
    // 相対モードで使用するときはMouseクラスにウィンドウハンドルを渡す必要がある
    // mouse.SetWindow( hWnd );

    // 入力情報を更新
    state_ = mouse_.GetState();
}